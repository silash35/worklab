import sympy as sp
import numpy as np
import matplotlib.pyplot as plt

x: sp.Symbol = sp.symbols("x")

# Definição da função
t = 0.05
C = 10**-4
L = 5
funçãoAnalítica = (
    sp.exp((x * t) / (2 * L)) * sp.cos(t * sp.sqrt((1 / (L * C)) - (x / (2 * L)) ** 2))  # type: ignore
    - 0.01
)

# Gera o arquivo latex.md
markdown = open("latex.md", "w")
markdown.write("# Função:\n\n")
markdown.write(f"$${sp.latex(funçãoAnalítica)}$$")
markdown.close()

# Gera função numérica
funçãoNumérica = sp.lambdify(x, funçãoAnalítica, "numpy")

# Cria Vetor com possíveis valores de x para teste da função
vX = np.linspace(300, 350, 100)  # Start, End, Number of Points
vY = funçãoNumérica(vX)

# Plota o gráfico
plt.legend(["Função"])
plt.axhline(0, color="black", linewidth=0.5)
plt.plot(vX, vY)
plt.show()
