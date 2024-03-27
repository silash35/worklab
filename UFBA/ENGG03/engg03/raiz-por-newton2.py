import numpy as np
from scipy.optimize import fsolve


# Questão 1: Projeto de circuito
def q(x: float):
    t = 0.05
    C = 10**-4
    L = 5
    return (
        np.exp((x * t) / (2 * L))
        * np.cos(t * np.sqrt((1 / (L * C)) - (x / (2 * L)) ** 2))
        - 0.01
    )


print("Projeto de circuito:")
raiz = fsolve(q, 300)
print("A raiz da função:", raiz)
print()


# Questão 2: Fator de Fricção
def colebrook(x: float):
    rho = 1.23
    mu = 1.79e-5
    D = 0.005
    epsilon = 1.5e-6
    v = 40
    Re = (rho * v * D) / mu
    return -2 * np.log10((epsilon / (3.7 * D)) + (2.51 / (Re * np.sqrt(x)))) - (
        1 / np.sqrt(x)
    )


print("Fator de Fricção:")
raiz = fsolve(colebrook, 0.01)
print("A raiz da função:", raiz)
print()
