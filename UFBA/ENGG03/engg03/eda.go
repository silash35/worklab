function adicionar_fila(fila, novo_nó):
    if fila->inicio == λ then
        fila->inicio = novo_nó
    else:
        if novo_nó->prioridade then
            atual = fila->inicio
            if atual == λ || !atual->prioridade then
                novo_nó->proximo = fila->inicio
                fila->inicio = novo_nó
            else
                while atual->proximo != && λ atual->proximo->prioridade do
                    atual = atual->proximo
                novo_nó->proximo = atual->proximo
                atual->proximo = novo_nó
        else
            atual = fila->inicio
            while atual->proximo =! λ do
                atual = atual->proximo
            atual->proximo = novo_nó
    return novo_nó

function remover_fila(fila):
    if fila->inicio == λ then
        print("Fila está vazia")
        return λ
    else:
        removido = fila->inicio
        fila->inicio = fila->inicio->proximo
        return removido

new(fila)
fila->inicio = λ

bool sair = false
while !sair do
    print("Selecione uma opção:")
    print("1 - Adicionar à fila")
    print("2 - Remover da fila")
    print("3 - Sair")
    opção = input()

    if opção == 1 then
        print("Adicionando à fila")
        new(nó)

        print("Nome: ")
        string nome = input()
        nó->nome = nome

        print("Prioridade (s/N): ")
        bool prioridade = input() == "s"
        nó->prioridade = prioridade

        string senha = gerar_senha()
        nó->senha = senha
        print("Guarde a senha:", senha)

        nó->proximo = λ
        adicionar_fila(fila, nó)
    else if opção == 2:
        print("Removendo da fila")
        nó = remover_fila(fila)
        if nó != λ:
            print("Nó removido:")
            print("Nome: " + nó->nome + ", Senha: " + nó->senha)
            delete(nó)

    else if opção == 3:
        sair = true

delete(fila)