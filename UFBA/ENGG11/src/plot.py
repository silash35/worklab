import matplotlib.pyplot as plt


def plot_tanks(t, tanks, labels=None):
    plt.figure(figsize=(10, 4), layout="constrained")
    plt.title("Níveis dos tanques pelo tempo")

    for i, tank in enumerate(tanks):
        label = labels[i] if (type(labels) is list) else labels
        plt.plot(t, tank, label=label)
    plt.xlabel("Tempo (s)")
    plt.ylabel("Nível (cm)")
    plt.legend()
    plt.show()
