import numpy as np
import torch
from scipy.integrate import solve_ivp

np.random.seed(42)

# Constantes
a1 = 50  # cm^2
a2 = 50  # cm^2
cv1 = 1
cv2 = 1


def F(t, op=np):
    f = -op.tanh(((t) / (20)) - 5) * 2.5 + 2.8
    return f


def edo_np(t, Y):
    h1, h2 = Y[0], Y[1]

    # Tanks limits
    h1 = np.where(h1 < 0.0, 0.0, h1)
    h2 = np.where(h2 < 0.0, 0.0, h2)

    # Equations
    dh1dt = (F(t) - cv1 * np.sqrt(h1)) / a1
    dh2dt = (cv1 * np.sqrt(h1) - cv2 * np.sqrt(h2)) / a2
    return np.array([dh1dt, dh2dt])


def edo_torch(t, Y):
    h1, h2 = Y

    # Equations
    dh1dt = (F(t, torch) - cv1 * torch.sqrt(h1)) / a1
    dh2dt = (cv1 * torch.sqrt(h1) - cv2 * torch.sqrt(h2)) / a2
    return [dh1dt, dh2dt]


def simulate(y0, t_eval):
    sol = solve_ivp(edo_np, [t_eval[0], t_eval[-1]], y0, t_eval=t_eval)
    return sol.y
