import numpy as np

x = np.array([0.0, 0.2, 0.4, 0.6, 0.8, 1.0])
y = np.array([0.0, 7.78, 10.68, 8.38, 3.97, 0.0])


# Calcular derivada
def derivada(x, y):
    dydx = np.zeros(len(x))
    for i in range(len(x)):
        if i == 0:
            dydx[i] = (y[i + 1] - y[i]) / (x[i + 1] - x[i])
        elif i == (len(x) - 1):
            dydx[i] = (y[i] - y[i - 1]) / (x[i] - x[i - 1])
        else:
            dydx[i] = (y[i + 1] - y[i - 1]) / (x[i + 1] - x[i - 1])
    return dydx


El = 1.2e7

M = -derivada(x, derivada(x, y)) * El

print(M)
