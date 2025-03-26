import numpy as np

# Criando a matriz dos coeficientes
A = np.array(
    [
        [np.sin(1), np.cos(1), np.sin(2 * 1), np.cos(2 * 1)],
        [np.sin(2), np.cos(2), np.sin(2 * 2), np.cos(2 * 2)],
        [np.sin(3), np.cos(3), np.sin(2 * 3), np.cos(2 * 3)],
        [np.sin(4), np.cos(4), np.sin(2 * 4), np.cos(2 * 4)],
    ]
)

# Criando o vetor das constantes
b = np.array([[1], [2], [3], [4]])

# Resolvendo o sistema linear
sol = np.linalg.solve(A, b)

# Imprimindo a solução
print("A1 =", sol[0, 0])
print("B1 =", sol[1, 0])
print("A2 =", sol[2, 0])
print("B2 =", sol[3, 0])

# Validando a solução
print(A.dot(sol))
