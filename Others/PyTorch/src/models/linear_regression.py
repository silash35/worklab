from torch import nn
import torch


class LinearRegressionModel(nn.Module):
    def __init__(self, in_size: int = 1, out_size: int = 1):
        super().__init__()
        self.linear_layer = nn.Linear(in_size, out_size)

    def forward(self, x: torch.Tensor) -> torch.Tensor:
        return self.linear_layer(x)
