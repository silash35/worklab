import torch


def dydx(x, y):
    return torch.autograd.grad(
        y, x, grad_outputs=torch.ones_like(y), create_graph=True
    )[0]


def mean_square(x):
    return torch.mean(x**2)


def train(
    model,
    loss_fn,
    optimizer,
    epochs,
    t: torch.Tensor,
    target_loss: None | float = None,
    early_stopping: None | int = None,
):
    loss_value = 0
    smaller_loss = 9999999
    not_evolved_counter = 0

    for epoch in range(epochs):
        # Coloca o modelo no modo de treinamento
        model.train()

        # Calcula o loss usando a nossa função loss.
        loss = loss_fn(model, t)

        # Ajusta os valores do modelo
        optimizer.zero_grad()
        loss.backward()
        optimizer.step()

        loss_value = float(loss.detach().numpy())
        if target_loss is not None and loss_value < target_loss:
            break

        if loss_value < smaller_loss:
            not_evolved_counter = 0
            smaller_loss = loss_value
        else:
            not_evolved_counter += 1

        if early_stopping is not None and not_evolved_counter >= early_stopping:
            print("Early stopping at", epoch)
            break

    return loss_value


def save_performance_table(
    methods: list[str],
    training_losses: list[float],
    validation_losses: list[float],
    filename: str,
    label: str,
):
    if not (len(methods) == len(training_losses) == len(validation_losses)):
        raise ValueError("All input lists must have the same length")

    table_rows = [
        f"{method} & {train:.4f} & {val:.4f} \\\\"
        for method, train, val in zip(methods, training_losses, validation_losses)
    ]

    table = rf"""
\begin{{table}}[ht]
    \centering
    \caption{{Valores da função objetivo e métrica de validação}}
    \begin{{tabularx}}{{0.45\textwidth}}{{ccc}}
    \hline
    \makecell{{Método}} & \makecell{{Função \\ Objetivo}} & \makecell{{Métrica de \\ validação}} \\
    \hline
    {f"{chr(10)}    ".join(table_rows)}
    \hline
    \end{{tabularx}}
    \label{{{label}}}
\end{{table}}
""".strip()

    with open(filename, "w") as f:
        f.write(table)
