import numpy as np

# Criando a matriz dos coeficientes
A = np.array(
    [
        [np.sin(1.0), np.cos(1.0), np.sin(2.0 * 1.0), np.cos(2.0 * 1.0)],
        [np.sin(2.0), np.cos(2.0), np.sin(2.0 * 2.0), np.cos(2.0 * 2.0)],
        [np.sin(3.0), np.cos(3.0), np.sin(2.0 * 3.0), np.cos(2.0 * 3.0)],
        [np.sin(4.0), np.cos(4.0), np.sin(2.0 * 4.0), np.cos(2.0 * 4.0)],
    ]
)

# Criando o vetor das constantes
b = np.array([[1.0], [2.0], [3.0], [4.0]])

# Resolvendo o sistema linear
sol = np.linalg.solve(A, b)

# Imprimindo a solução
print("A1 =", sol[0, 0])
print("B1 =", sol[1, 0])
print("A2 =", sol[2, 0])
print("B2 =", sol[3, 0])

# Validando a solução
# Validando a resposta
print(A.dot(sol))
