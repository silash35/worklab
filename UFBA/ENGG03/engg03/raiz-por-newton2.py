import sympy as sp
from scipy.optimize import fsolve

x: sp.Symbol = sp.symbols("x")

# Questão 1: Projeto de circuito
t = 0.05
C = 10**-4
L = 5
funçãoAnalítica = (
    sp.exp((x * t) / (2 * L)) * sp.cos(t * sp.sqrt((1 / (L * C)) - (x / (2 * L)) ** 2))
    - 0.01
)

# Solução
print("Projeto de circuito:")
q = sp.lambdify(x, funçãoAnalítica, "numpy")  # Conversão para função numérica
raiz = fsolve(q, 300)
print("A raiz da função:", raiz)
print("Teste da raiz:", q(raiz))
print()


# Questão 2: Fator de Fricção
rho = 1.23
mu = 1.79e-5
D = 0.005
epsilon = 1.5e-6
v = 40
Re = (rho * v * D) / mu
funçãoAnalítica = 2 * sp.log((epsilon / (3.7 * D)) + (2.51 / (Re * sp.sqrt(x))), 10) + (
    1 / sp.sqrt(x)
)

# Solução
print("Fator de Fricção:")
colebrook = sp.lambdify(x, funçãoAnalítica, "numpy")
raiz = fsolve(colebrook, 0.01)  # Conversão para função numérica
print("A raiz da função:", raiz)
print("Teste da raiz:", colebrook(raiz))
print()
