import numpy as np


def f1(x0, x1):
    return (x0**2) / 3 + x1**2 - 1


def f2(x0, x1):
    return x0**2 + (x1**2) / 4 - 1


def derivada_x0(f, x0, x1, h=0.00000001):
    return (f(x0 + h, x1) - f(x0 - h, x1)) / (2 * h)


def derivada_x1(f, x0, x1, h=0.00000001):
    return (f(x0, x1 + h) - f(x0, x1 - h)) / (2 * h)


Ki = [[1], [1]]  # Chute inicial
tol = 1e-8  # Tolerância
erro = 1

while abs(erro) > tol:
    fKi = np.array([[f1(Ki[0][0], Ki[1][0]), f2(Ki[0][0], Ki[1][0])]]).T

    erro = fKi.T.dot(fKi)[0, 0]

    # Matriz Jacobiana
    JKi = [
        [derivada_x0(f1, Ki[0][0], Ki[1][0]), derivada_x1(f1, Ki[0][0], Ki[1][0])],
        [derivada_x0(f2, Ki[0][0], Ki[1][0]), derivada_x1(f2, Ki[0][0], Ki[1][0])],
    ]

    # Newton-Raphson
    # Ki+1 = Ki - f(Ki) / f´(Ki)
    # Ki+1 = Ki - inv(J(Ki))*f(Ki)
    Ki = Ki - np.linalg.inv(JKi).dot(fKi)


print("x0 = ", Ki[0][0])
print("x1 = ", Ki[1][0])
