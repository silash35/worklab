from scipy.optimize import minimize

consumo_gasolina = 14  # litros por km
consumo_álcool = 11  # litros por km

capacidade_tanque = 50  # litros

preço_gasolina = 6.00  # reais por litro
preço_álcool = 4.20  # reais por litro

dinheiro_disponível = 100.00  # reais


# Função para maximizar
def distancia(X: list[float]):
    q_gasolina, q_álcool = X
    distancia = q_gasolina * consumo_gasolina + q_álcool * consumo_álcool
    return distancia


# Restrições
def custo(X: list[float]):
    q_gasolina, q_álcool = X
    custo = q_gasolina * preço_gasolina + q_álcool * preço_álcool
    return custo


def volume(X: list[float]):
    q_gasolina, q_álcool = X
    capacidade = q_gasolina + q_álcool
    return capacidade


limites = [(0, None), (0, None)]

restrições = [
    {"type": "ineq", "fun": lambda X: capacidade_tanque - volume(X)},
    {"type": "ineq", "fun": lambda X: dinheiro_disponível - custo(X)},
]


# Otimização
x0 = [0.0, 0.0]  # chute inicial
res = minimize(lambda X: -distancia(X), x0, bounds=limites, constraints=restrições)

print("Custo:", custo(res.x), "reais")
print("Distância:", distancia(res.x), "km")
