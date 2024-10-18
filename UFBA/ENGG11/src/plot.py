import matplotlib.pyplot as plt
import numpy as np

from typings import Population

save_folder = "../images/"


def plot_tanks(t, tanks, labels=None, filename: str | None = None):
    plt.figure(figsize=(10, 4), layout="constrained", dpi=300)
    plt.title("Níveis dos tanques pelo tempo")

    for i, tank in enumerate(tanks):
        label = labels[i] if (type(labels) is list) else labels
        plt.plot(t, tank, label=label)
    plt.xlabel("Tempo (s)")
    plt.ylabel("Nível (cm)")
    plt.legend()

    if filename is None:
        plt.show()
    else:
        plt.savefig(save_folder + filename)
        plt.clf()


def plot_space(
    Cv1, Cv2, Z, individuals: None | Population, filename: str | None = None
):
    plt.figure(figsize=(16, 9), layout="constrained", dpi=300)
    plt.contourf(
        Cv1,
        Cv2,
        Z ** (1 / 8),
        levels=200,
        alpha=1 if individuals is None else 0.5,
        antialiased=False if individuals is None else True,
    )
    if individuals is None:
        plt.colorbar()
    plt.xlabel("$Cv_1$")
    plt.ylabel("$Cv_2$")
    plt.title("Visualização gráfica da função objetivo")

    if individuals is not None:
        best_fitness = np.max([individual["fitness"] for individual in individuals])
        for individual in individuals:
            if individual["fitness"] == best_fitness:
                plt.scatter(
                    individual["chromosome"][0],
                    individual["chromosome"][1],
                    color="green",
                )
            else:
                plt.scatter(
                    individual["chromosome"][0],
                    individual["chromosome"][1],
                    color="red",
                )

    if filename is None:
        plt.show()
    else:
        plt.savefig(save_folder + filename)
        plt.clf()
