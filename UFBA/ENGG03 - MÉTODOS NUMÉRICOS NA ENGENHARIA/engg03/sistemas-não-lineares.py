from scipy.optimize import fsolve
import numpy as np


# Questão 1a: Tanque cascata
def dh(h):
    h1 = h[0]
    h2 = h[1]

    Ft = 2000  # cm³/min
    Cv1 = 445.0  # cm²/min
    Cv2 = 516.0  # cm²/min
    A1 = 116  # cm²
    A2 = 320  # cm²

    dh1 = (Ft - Cv1 * np.sqrt(h1)) / A1
    dh2 = (Cv1 * np.sqrt(h1) - Cv2 * np.sqrt(h2)) / A2
    F = np.array([dh1, dh2])
    return F


print("Tanque cascata:")
X0 = np.array([1, 1])  # Chute inicial
X = fsolve(dh, X0)
print("Solução do sistema:", X)
print("Teste da solução do sistema:", dh(X))
print()


# Questão 1b: Tanque cascata
def dh2(h2):
    Cv1 = 445.0  # cm²/min
    Cv2 = 516.0  # cm²/min
    A2 = 320  # cm²

    return (Cv1 * np.sqrt(30) - Cv2 * np.sqrt(h2)) / A2


print("Tanque cascata (continuação):")
X0 = 1  # Chute inicial
X = fsolve(dh2, X0)
print("Solução do sistema:", X)
print("Teste da solução do sistema:", dh2(X))
print()
