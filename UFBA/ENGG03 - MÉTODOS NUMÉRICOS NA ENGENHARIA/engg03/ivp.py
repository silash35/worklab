import numpy as np
from scipy.integrate import solve_ivp
import matplotlib.pyplot as plt

# Construindo função analítica
# Definindo o valor das constantes
c, A = [0.25, 1.0]

# Definindo a condição inicial
h0 = 1.0

# Definindo o tempo de simulação
t = np.linspace(0, 10, 100)


# Definindo a função analítica
def sol_analítica(t):
    return (np.sqrt(h0) - c / (2 * A) * t) ** 2


plt.plot(t, sol_analítica(t))


# Definindo a solução pela EDO
def edo(t, h):
    return -c * np.sqrt(h) / A


sol_edo = solve_ivp(edo, (0, 10), [h0], t_eval=t)


plt.plot(sol_edo.t, sol_edo.y[0])
plt.show()
