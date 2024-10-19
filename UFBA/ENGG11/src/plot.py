import matplotlib.pyplot as plt
import numpy as np

from typings import Population

save_folder = "../media/"
default_dpi = 96


def save_or_show(filename: str | None = None):
    if filename is None:
        plt.show()
    else:
        plt.savefig(save_folder + filename)
        plt.clf()
        plt.close()


def plot_tanks(t, tanks, labels=None, filename: str | None = None):
    plt.figure(figsize=(10, 4), layout="constrained", dpi=default_dpi)
    plt.title("Níveis dos tanques pelo tempo")

    for i, tank in enumerate(tanks):
        label = labels[i] if (type(labels) is list) else labels
        plt.plot(t, tank, label=label)
    plt.xlabel("Tempo (s)")
    plt.ylabel("Nível (cm)")
    plt.legend()

    save_or_show(filename)


def plot_space(Cv1, Cv2, Z, filename: str | None = None):
    plt.figure(figsize=(16, 9), layout="constrained", dpi=default_dpi)
    plt.contourf(Cv1, Cv2, Z ** (1 / 8), levels=200, alpha=1)
    plt.colorbar()
    plt.xlabel("$Cv_1$")
    plt.ylabel("$Cv_2$")
    plt.title("Visualização gráfica da função objetivo")

    save_or_show(filename)


def plot_population(Cv1, Cv2, Z, population: Population, filename: str | None = None):
    plt.figure(figsize=(16, 9), layout="constrained", dpi=default_dpi)
    plt.contourf(Cv1, Cv2, Z ** (1 / 8), levels=200, alpha=0.5, antialiased=True)

    plt.xlabel("$Cv_1$")
    plt.ylabel("$Cv_2$")
    plt.title("Posição dos indivíduos da população")

    best_fitness = np.max([individual["fitness"] for individual in population])
    for individual in population:
        if individual["fitness"] == best_fitness:
            plt.scatter(
                individual["chromosome"][0], individual["chromosome"][1], color="green"
            )
        else:
            plt.scatter(
                individual["chromosome"][0], individual["chromosome"][1], color="red"
            )

    save_or_show(filename)
