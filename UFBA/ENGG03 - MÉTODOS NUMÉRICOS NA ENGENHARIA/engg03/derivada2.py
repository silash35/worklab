def derivada(x, y):
    dydx = np.zeros(len(x))
    for i in range(len(x)):
        if i == 0:
            dydx[i] = (y[i + 1] - y[i]) / (x[i + 1] - x[i])
        elif i == (len(x) - 1):
            dydx[i] = (y[i] - y[i - 1]) / (x[i] - x[i - 1])
        else:
            dydx[i] = (y[i + 1] - y[i - 1]) / (x[i + 1] - x[i - 1])
    return dydx


import pandas as pd
import numpy as np

# Lendo os dados da planilha
sheet_url = "https://docs.google.com/spreadsheets/d/1T7-Lc3Ewo3NRskVWBtZ5vGGTFeCZa3re6dboKq-2cTc/edit#gid=0"
url_1 = sheet_url.replace("/edit#gid=", "/export?format=csv&gid=")
arquivo = pd.read_csv(url_1, decimal=",")

# Separando os dados
t = arquivo["t"].to_numpy()

r = arquivo["r"].to_numpy()
dr = derivada(t, r)
d2r = derivada(t, dr)

theta = arquivo["theta"].to_numpy()
dtheta = derivada(t, theta)
d2theta = derivada(t, dtheta)

# Calculando a velocidade e a aceleração
v = np.sqrt(dr**2 + (r * dtheta) ** 2)
a = np.sqrt((d2r - r * (dtheta**2)) ** 2 + (r * d2theta + 2 * dr * dtheta) ** 2)

# Exibindo os dados
import matplotlib.pyplot as plt

plt.subplot(1, 2, 1)
plt.title("Velocidade x tempo")
plt.ylabel("Velocidade (km/s)")
plt.xlabel("Tempo (s)")
plt.plot(t, v, ".-")

plt.subplot(1, 2, 2)
plt.title("Aceleração x tempo")
plt.ylabel("Aceleração (km/s²)")
plt.xlabel("Tempo (s)")
plt.plot(t, a, ".-", label="Aceleração")

plt.grid(True)
plt.tight_layout()
plt.show()
