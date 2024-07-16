import random
import string


# Gerar uma senha aleatória
def gerar_senha():
    return "".join(random.choices(string.ascii_uppercase, k=6))


def criar_nó(nome: str, prioridade: bool):
    return {
        "nome": nome,
        "senha": gerar_senha(),
        "prioridade": prioridade,
        "proximo": None,
    }


def criar_fila():
    return {"proximo": None, "prioridade": False}


def adicionar_fila(fila, novo_nó):
    if fila["proximo"] is None:
        fila["proximo"] = novo_nó
        return novo_nó

    if fila["proximo"]["prioridade"] is False and novo_nó["prioridade"] is True:
        novo_nó["proximo"] = fila["proximo"]
        fila["proximo"] = novo_nó
        return novo_nó

    if novo_nó["prioridade"] is False:
        atual = fila["proximo"]
        while atual["proximo"] is not None:
            atual = atual["proximo"]
        atual["proximo"] = novo_nó
        return novo_nó

    # PP NN P NN
    if novo_nó["prioridade"] is True:
        conta_comum = 0
        conta_prioridade = 0

        atual = fila["proximo"]

        while atual["proximo"] is not None:
            if atual["prioridade"] is False:
                conta_comum += 1
                conta_prioridade = 0
            else:
                conta_prioridade += 1
                conta_comum = 0
            atual = atual["proximo"]

            if conta_comum == 2 or conta_prioridade == 1:
                break
            if conta_comum == 1 or conta_prioridade == 1:
                break

        novo_nó["proximo"] = atual["proximo"]
        atual["proximo"] = novo_nó

    return novo_nó


def remover_fila(fila):
    if fila["proximo"] is None:
        print("Fila está vazia")
        return None
    else:
        removido = fila["proximo"]
        fila["proximo"] = fila["proximo"]["proximo"]
        return removido


fila = criar_fila()

adicionar_fila(fila, criar_nó("3", False))
adicionar_fila(fila, criar_nó("4", False))
adicionar_fila(fila, criar_nó("1", True))
adicionar_fila(fila, criar_nó("2", True))
adicionar_fila(fila, criar_nó("7", False))
adicionar_fila(fila, criar_nó("8", False))
adicionar_fila(fila, criar_nó("5", True))
adicionar_fila(fila, criar_nó("6", True))

sair = False
for _ in range(8):
    nó = remover_fila(fila)
    if nó is not None:
        print("Nó removido:")
        print(f"Nome: {nó['nome']}, Senha: {nó['senha']}")

# s s n n s s n n
# 1 2 3 4 5 6 7 8
