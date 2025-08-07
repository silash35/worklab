import numpy as np


def tempo_de_estabilização(t, var, SP, tol=0.01):
    var = np.asarray(var)
    t = np.asarray(t)

    # Define limites superior e inferior
    lim_sup = SP * (1 + tol)
    lim_inf = SP * (1 - tol)

    # Verifica se em cada tempo a pressão está dentro da faixa permitida
    dentro_da_faixa = (var >= lim_inf) & (var <= lim_sup)

    # Para estabilizar, deve permanecer dentro da faixa até o final
    for i in range(len(t)):
        if dentro_da_faixa[i:].all():
            return t[i]

    # Se nunca estabilizou
    raise ValueError("A variável não estabilizou dentro da faixa permitida.")

def calcular_metricas_erro_normalizado(t, pm, SP_t):
    t = np.asarray(t)
    pm = np.asarray(pm)
    SP_t = np.asarray(SP_t)

    # Evita divisão por zero — se tiver SP_t muito próximo de zero
    SP_t[SP_t == 0] = 1e-6

    erro_norm = (SP_t - pm) / SP_t

    iae = np.trapezoid(np.abs(erro_norm), t)
    ise = np.trapezoid(erro_norm ** 2, t)
    itae = np.trapezoid(t * np.abs(erro_norm), t)

    return iae, ise, itae
