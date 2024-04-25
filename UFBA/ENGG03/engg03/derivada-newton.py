import numpy as np


def f1(x0, x1):
    return (x0**2) / 3 + x1**2 - 1


def f2(x0, x1):
    return x0**2 + (x1**2) / 4 - 1


def derivadas(f, x0, x1, h=0.00000001):
    dfdx0 = (f(x0 + h, x1) - f(x0 - h, x1)) / (2 * h)
    dfdx1 = (f(x0, x1 + h) - f(x0, x1 - h)) / (2 * h)
    return np.array([dfdx0, dfdx1])


Ki = [[1], [1]]  # Chute inicial
while True:
    fKi = np.array([[f1(Ki[0][0], Ki[1][0]), f2(Ki[0][0], Ki[1][0])]]).T

    # Critério de parada
    if abs(fKi.T.dot(fKi)[0, 0]) < 1e-8:
        break

    # Montando a Jacobiana
    df1dx0, df1dx1 = derivadas(f1, Ki[0][0], Ki[1][0])
    df2dx0, df2dx1 = derivadas(f2, Ki[0][0], Ki[1][0])
    JKi = [
        [df1dx0, df1dx1],
        [df2dx0, df2dx1],
    ]

    # Newton-Raphson
    # Ki+1 = Ki - f(Ki) / f´(Ki)
    # Ki+1 = Ki - inv(J(Ki))*f(Ki)
    Ki = Ki - np.linalg.inv(JKi).dot(fKi)


print("x0 = ", Ki[0][0])
print("x1 = ", Ki[1][0])
