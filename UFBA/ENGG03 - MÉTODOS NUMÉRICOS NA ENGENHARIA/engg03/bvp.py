import numpy as np
import matplotlib.pyplot as plt
from scipy.integrate import solve_bvp, solve_ivp


# Redução de ordem
def edo(x, Y):
    # Constantes
    k = [167.0, 9.45e-8]
    T_s = 293
    # Variáveis dependentes
    T = Y[0]  # Temperatura
    w = Y[1]  # Calor
    # Edos
    dTdx = w
    dwdx = k[0] * (T - T_s) + k[1] * (T**4 - T_s**4)
    return np.array([dTdx, dwdx])


x = np.linspace(0, 0.1, 100)  # Comprimento da barra
T0, Tf = 493.0, 293.0  # Condição inicial e final


def loss_bc(Y_0, Y_f):
    # Inicio
    T0_prev, W0_prev = Y_0
    # Final
    Tf_prev, Wf_prev = Y_f

    return [T0_prev - T0, Tf_prev - Tf]


# Estimativa inicial
T_est = np.linspace(T0, Tf, len(x))
w_est = np.gradient(T_est, x)
Y_est = np.vstack([T_est, w_est])

# Resolvendo o problema de valor de contorno
sol_bvp = solve_bvp(edo, loss_bc, x, Y_est)
T_bvp = sol_bvp.y[0]

# Plotando o gráfico
plt.plot(x, T_bvp, label="Temperatura")
plt.plot(x[-1], Tf, "o", label="Temperatura final")
plt.xlabel("Comprimento")
plt.ylabel("Temperatura")
plt.grid()
plt.legend()
plt.show()
