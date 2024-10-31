import matplotlib.pyplot as plt
import plotly.graph_objects as go
import seaborn as sns

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


def plot_tanks(t, tanks, labels=None, filename: str | None = None, scatter=0):
    plt.figure(figsize=(10, 4), layout="constrained", dpi=default_dpi)

    for i, tank in enumerate(tanks):
        label = labels[i] if (type(labels) is list) else labels
        if i < scatter:
            plt.scatter(t, tank, label=label, s=8)
        else:
            plt.plot(t, tank, label=label)
    plt.xlabel("Tempo / s")
    plt.ylabel("Nível / cm")
    plt.legend()

    save_or_show(filename)


def plot_space(Cv1, Cv2, Z, filename: str | None = None):
    plt.figure(figsize=(16, 9), layout="constrained", dpi=default_dpi)
    plt.contourf(Cv1, Cv2, Z ** (1 / 8), levels=200, alpha=1)
    plt.colorbar()
    plt.xlabel("$Cv_1$")
    plt.ylabel("$Cv_2$")

    save_or_show(filename)


def plot_space_3d(Cv1, Cv2, Z, filename: str | None = None):
    fig = go.Figure(
        data=[go.Surface(z=Z ** (1 / 8), x=Cv1, y=Cv2)],
    )
    fig.update_traces(showscale=False)
    fig.update_layout(
        scene=dict(
            xaxis_title="Cv1",
            yaxis_title="Cv2",
            zaxis_title="Fitness",
        ),
        width=1080,
        height=720,
        margin=dict(r=20, l=10, b=10, t=10),
    )

    if filename is not None:
        fig.write_image(save_folder + filename)
    else:
        fig.show()


def plot_population(Cv1, Cv2, Z, population: Population, filename: str | None = None):
    plt.figure(figsize=(16, 9), layout="constrained", dpi=default_dpi)
    plt.contourf(Cv1, Cv2, Z ** (1 / 8), levels=200, alpha=0.5, antialiased=True)

    plt.xlabel("$Cv_1$")
    plt.ylabel("$Cv_2$")

    best_ind = max(population, key=lambda ind: ind["fitness"])
    population = [ind for ind in population if ind["fitness"] != best_ind["fitness"]]

    for ind in population:
        plt.scatter(ind["chromosome"][0], ind["chromosome"][1], color="red")

    plt.scatter(best_ind["chromosome"][0], best_ind["chromosome"][1], color="green")

    save_or_show(filename)


def plot_density(values, labels, metric, filename: str | None = None):
    plt.figure(figsize=(10, 5))

    for i in range(len(values)):
        sns.histplot(
            values[i],
            kde=True,
            label=labels[i],
            stat="density",
            bins=15,
        )

    plt.xlabel(metric)
    plt.ylabel("Densidade")
    plt.legend()

    save_or_show(filename)
