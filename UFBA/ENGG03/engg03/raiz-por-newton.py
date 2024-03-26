import sympy as sp
from typing import cast

x: sp.Symbol = sp.symbols("x")


# 1e-4 = 1*10^-4 = 0.0001
# 1e-11 = 1*10^-11 = 0.00000000001
def newton(f: sp.Expr, x0: float, tol=10e-11):
    df = sp.diff(f, x)

    def função(xValue: float):
        return cast(float, f.evalf(subs={x: xValue}))

    def derivada(xValue: float):
        return cast(float, df.evalf(subs={x: xValue}))

    maxIter = 100
    for i in range(maxIter):
        print("x" + str(i) + ":", x0)
        x1: float = x0 - (função(x0) / derivada(x0))
        x0 = x1
        if abs(função(x1)) < tol:
            return x1
    raise Exception("Falha ao encontrar a raiz")


print("E 3.4.1:")
F = sp.sympify("cos(x)-x**2")
print("Função:", F)
print("{:.5f}".format(newton(F, 1)))
print()

print("E 3.4.3:")
F = sp.sympify("exp(-(x**2)) - x")
print("Função:", F)
print("{:.8f}".format(newton(F, 1)))
print()
