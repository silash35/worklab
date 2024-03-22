import sympy as sp

x = sp.symbols("x")

def newton(F, x0, tol=0.00000000001):
    maxIter=100

    f  = sp.diff(F, x)
    for i in range(maxIter):
        print("x"+str(i)+":", x0)
        x1 = x0 - F.evalf(subs={x: x0}) / f.evalf(subs={x: x0})
        if abs(x1 - x0) < tol:
            return x1
        x0 = x1
    return None


print("E 3.4.1:")
F = sp.cos(x) - x**2
print("Função:", F)
print("{:.5f}".format(newton(F, 1)))
print()

print("E 3.4.3:")
F = sp.exp(-x**2) - x
print("Função:", F)
print("{:.8f}".format(newton(F, 1)))
print()