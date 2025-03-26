import numpy as np
from scipy.integrate import quad


def f(x):
    return 3.0 * np.exp(-0.2 * (x + 3.0)) * np.cos(2.0 * (x + 3.0))


# Intervalo de integração
a, b = [0, 10]

N = 200
x = np.linspace(a, b, N + 1)
y = f(x)


def integral_pontos(x, y):
    It = 0

    for i in range(len(x) - 1):
        It += ((y[i] + y[i + 1]) * (x[i + 1] - x[i])) / 2

    return It


print("Integral por trapézios:", integral_pontos(x, y))
print("Integral pelo scipy:", quad(f, a, b)[0])
