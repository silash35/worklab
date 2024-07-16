from numpy import float32
from torch import nn
import torch
from torch.optim import Optimizer
from torch.nn.modules.loss import _Loss
import numpy as np


def trainer(
    model: nn.Module,
    loss_fn: _Loss,
    optimizer: Optimizer,
    X_train: torch.Tensor,
    y_train: torch.Tensor,
    X_test: torch.Tensor,
    y_test: torch.Tensor,
    epochs=100,
    verbose=True,
):
    train_loss_values: list[np.float32] = []
    test_loss_values: list[np.float32] = []
    epoch_count: list[int] = []

    for epoch in range(epochs):
        model.train()

        y_pred = model(X_train)
        loss = loss_fn(y_pred, y_train)
        optimizer.zero_grad()
        loss.backward()
        optimizer.step()

        model.eval()

        with torch.inference_mode():
            test_pred = model(X_test)
            test_loss = loss_fn(test_pred, y_test)
            if epoch % 10 == 0:
                epoch_count.append(epoch)
                train_loss_values.append(loss.detach().numpy())
                test_loss_values.append(test_loss.detach().numpy())
                if verbose:
                    print(
                        f"Epoch: {epoch} | Train Loss: {loss} | Test Loss: {test_loss}"
                    )

    return train_loss_values, test_loss_values, epoch_count
