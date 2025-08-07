import torch
from torch import nn


class BaseModel(nn.Module):
    def __init__(self, max_input: float, max_output: float):
        super().__init__()
        input_size = 1  # t
        hidden_size = 8
        output_size = 2  # h1, h2

        self.max_input = max_input
        self.max_output = max_output

        self.hidden_layer = nn.Sequential(
            nn.Linear(input_size, hidden_size),
            nn.Tanh(),
            nn.Linear(hidden_size, hidden_size),
            nn.Tanh(),
            nn.Linear(hidden_size, output_size),
        )

    def forward(self, x):
        output = self.hidden_layer((x * 2 / self.max_input) - 1)
        return torch.sqrt((output + 1) ** 2 + 1e-6) * (self.max_output / 2)
