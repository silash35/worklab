import matplotlib.pyplot as plt
import numpy as np
import seaborn as sns


def plot_density(values, label, unit, unit_first=False, kde=True):
    plt.figure(figsize=(8, 5), layout="constrained")
    mean_value = np.mean(values)
    sns.histplot(
        values,
        kde=kde,
        stat="density",
        bins=50,
        color="tab:blue",
    )
    plt.axvline(
        mean_value,
        linestyle="--",
        linewidth=1.5,
        color="tab:blue",
        label=f"Média: {unit if unit_first else ""}{mean_value:.2f}{"" if unit_first else unit}",
    )

    plt.xlabel(f"{label} ({unit})")
    plt.ylabel("Densidade de Probabilidade")
    plt.legend()
    plt.show()
