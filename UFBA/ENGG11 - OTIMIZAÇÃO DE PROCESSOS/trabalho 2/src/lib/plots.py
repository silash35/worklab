import matplotlib.pyplot as plt
import numpy as np
import seaborn as sns
from matplotlib import colors as mcolors

default_dpi = 300
save_folder = "../figures/"
plt.rcParams.update({"font.size": 18})
colors = list(mcolors.TABLEAU_COLORS.keys())


def save_or_show(filename: str | None = None):
    if filename is None:
        plt.show()
    else:
        plt.savefig(save_folder + filename)
        plt.clf()
        plt.close()


def plot_tanks(t, tanks, labels=None, filename: str | None = None, scatter=0):
    plt.figure(figsize=(8, 4), layout="constrained", dpi=default_dpi)

    for i, tank in enumerate(tanks):
        label = labels[i] if (type(labels) is list) else labels
        if i < scatter:
            plt.scatter(t, tank, label=label, s=8, alpha=0.5)
        else:
            plt.plot(t, tank, label=label)
    plt.xlabel("Tempo / s")
    plt.ylabel("Nível / cm")
    plt.grid(True)
    plt.legend()

    save_or_show(filename)


def plot_loss(loss_values, epoch_count, filename: str | None = None):
    plt.figure(figsize=(10, 4), layout="constrained", dpi=default_dpi)
    plt.plot(epoch_count, loss_values)
    plt.xlabel("Epoch")
    plt.ylabel("Loss")
    save_or_show(filename)


def plot_density(values, labels, filename: str | None = None, extra=None):
    # plt.rcParams.update({"font.size": 14})
    fig, ax = plt.subplots(2, figsize=(10, 6), layout="constrained", dpi=default_dpi)
    t_max = max([max(v) for v in values])

    for i in range(len(values)):
        mean_value = np.mean(values[i])
        sns.histplot(
            values[i],
            kde=True,
            stat="density",
            # bins=15,
            color=colors[i],
            ax=ax[i],
        )
        ax[i].axvline(
            mean_value,
            linestyle="--",
            linewidth=1.5,
            color=colors[i],
            label=f"{labels[i]}: {mean_value:.1f}s",
        )
        ax[i].set_xlabel(None)
        ax[i].set_ylabel(None)
        ax[i].set_xlim(0, t_max)
        ax[i].legend()

    if extra is not None:
        extra(plt)

    fig.supxlabel("Tempo / s")
    fig.supylabel("Densidade de Probabilidade")
    save_or_show(filename)
