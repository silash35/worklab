import sympy as sp
from typing import cast

x: sp.Symbol = sp.symbols("x", real=True)


# 1e-4 = 1*10^-4 = 0.0001
# 1e-11 = 1*10^-11 = 0.00000000001
def newton(f: sp.Expr, xn: float, tol=10e-11):
    """
    Função de Newton para encontrar a raiz de uma função f(x).

    A função retorna a raiz de f(x) a partir de um valor inicial x0.
    O método é aplicado até que a função retorne um valor abs(f(x)) < tol,
    que significa que a raiz foi achada com precisão suficiente.

    Caso a raiz não seja encontrada em 100 iterações, o método
    levanta uma exceção indicando falha.

    Os parâmetros são:
        f: a função a ser procurada a raiz
        x0: valor inicial para a iteração
        tol: tolerância para considerar que a raiz foi encontrada

    """
    df = sp.diff(f, x)  # derivada da função f(x)

    def função(xValue: float):
        """
        Função que retorna o valor de f(x) a partir de um valor x
        """
        return cast(
            float, f.evalf(subs={x: xValue})
        )  # evalf executa a função f(x) com x = xValue

    def derivada(xValue: float):
        """
        Função que retorna o valor da derivada de f(x) a partir de um valor x
        """
        return cast(
            float, df.evalf(subs={x: xValue})
        )  # evalf executa a derivada de f(x) com x = xValue

    maxIter = 100  # máximo de iterações
    for i in range(maxIter):  # loop de iteração
        print(f"x{i}:", xn)  # imprime valor atual de x
        xn = xn - (função(xn) / derivada(xn))  # iteração de Newton
        if abs(função(xn)) < tol:  # condição de parada
            return xn  # retorna a raiz encontrada
    raise Exception("Falha ao encontrar a raiz")  # erro de falha em encontrar a raiz


print("Projeto de circuito:")
t = 0.05
C = 10**-4
L = 5
F = (
    sp.exp((x * t) / (2 * L)) * sp.cos(t * sp.sqrt((1 / (L * C)) - (x / (2 * L)) ** 2))
    - 0.01
)
print("Função:", F)
print("{:.5f}".format(newton(F, 200)))
print()


print("Fator de Fricção:")
rho = 1.23
mu = 1.79e-5
D = 0.005
epsilon = 1.5e-6
v = 40
Re = (rho * v * D) / mu
F = -2 * sp.log((epsilon / (3.7 * D)) + (2.51 / (Re * sp.sqrt(x))), 10) - (
    1 / sp.sqrt(x)
)
print("Função:", F)
print("{:.5f}".format(newton(F, 0.001)))
print()
