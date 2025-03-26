import numpy as np
import matplotlib.pyplot as plt
from scipy.integrate import solve_ivp

# Definir constantes do problema
Lx, Ly = 10, 10  # Dimensão da placa
alfa = 0.9  # Coeficiente de difusão
tf = 50.0  # Tempo final

# Definir parâmetros de simulação
nt, nx, ny = 100, 25, 25  # Numero de pontos

x = np.linspace(0, Lx, nx)
y = np.linspace(0, Ly, ny)
t = np.linspace(0, tf, nt)

dx = x[1] - x[0]
dy = y[1] - y[0]

# Estado Inicial
T0 = np.zeros((nx, ny))
T0[0, :] = 100
T0[-1, :] = 10
T0[:, 0] = 100
T0[:, -1] = 10

# Print estado inicial
plt.imshow(T0, cmap="plasma", vmin=0, vmax=100)
plt.colorbar()
plt.show()


def edp_dTdt(t, T):
    T = T.reshape((nx, ny))
    dTdt = np.zeros((nx, ny))

    for i in range(nx):
        for j in range(ny):
            if i == 0 or j == 0:
                dTdt[i, j] = 0
            elif i == (nx - 1) or j == (ny - 1):
                dTdt[i, j] = 0
            else:
                dTdt[i, j] = ((T[i + 1, j] - 2 * T[i, j] + T[i - 1, j]) / (dx**2)) + (
                    (T[i, j + 1] - 2 * T[i, j] + T[i, j - 1]) / (dy**2)
                )

    return dTdt.flatten()


sol = solve_ivp(edp_dTdt, [0, tf], T0.flatten(), t_eval=t)

T_simulado = np.zeros((len(t), nx, ny))
for i in range(len(t)):
    T_simulado[i] = sol.y[:, i].reshape((nx, ny))


import matplotlib.animation as animation

fig, ax = plt.subplots()
im = plt.imshow(T_simulado[0], cmap="plasma", vmin=0, vmax=100)
plt.colorbar()


def update(frame_number):
    im.set_array(T_simulado[frame_number])
    return [im]


ani = animation.FuncAnimation(fig, update, len(T_simulado), interval=50)
plt.show()
