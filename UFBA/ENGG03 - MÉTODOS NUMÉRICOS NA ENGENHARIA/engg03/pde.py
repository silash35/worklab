import numpy as np
import matplotlib.pyplot as plt
from scipy.integrate import solve_ivp

# Definir constantes
L = 10.0  # Comprimento da barra
beta = 0.9  # Coeficiente de troca térmica

# Discretização do espaço e do tempo
n_x = 50  # Número de pontos discretos em x
x = np.linspace(0, L, n_x)
dx = x[1] - x[0]
n_t = 300  # Número de pontos discretos em t
tf = 50  # Tempo final da simulação
t = np.linspace(0, tf, n_t)

# Condição inicial
T0 = np.zeros(n_x)
# T0 = np.sin(x)*np.sin(x)*25
T0[0] = 100  # Condição inicial em x = 0
T0[1:-1] = 25  # Condição inicial em x = 1, ..., L-1
T0[-1] = 25  # Condição inicial em x = L

# Print estado inicial
plt.plot(x, T0)
plt.xlabel("x")
plt.ylabel("T(0,x)")
plt.title("Estado inicial")
plt.show()


def edp_dTdt(t, T):
    # Criando o vetor
    dTdt = np.zeros(n_x)

    # Solução
    for i in range(1, n_x - 1):
        dTdt[i] = beta * (T[i - 1] - 2 * T[i] + T[i + 1]) / (dx**2)

    # Condições de contorno
    # Como ambas são zero, podemos comentar pois o np.zeros já deixou eles como zero
    # dTdt[0] = 0  # Condição de contorno x=0
    # dTdt[-1] = 0  # Condição de contorno x=L

    return dTdt


sol = solve_ivp(edp_dTdt, [0, tf], T0, t_eval=t)

# Imprimindo animação
import matplotlib.animation as animation

fig, ax = plt.subplots()
(line,) = ax.plot(x, sol.y[:, 0])


def update(frame_number):
    line.set_data(x, sol.y[:, frame_number])
    return (line,)


ani = animation.FuncAnimation(fig, update, len(sol.y[0]), interval=5)
plt.show()
