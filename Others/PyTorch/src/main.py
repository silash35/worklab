from tkinter import W
from matplotlib import pyplot as plt
import torch
from torch import nn
from visualize import plot_predictions

# Create *known* parameters
weight = 0.7
bias = 0.3

# Create data
X = torch.arange(start=0, end=1, step=0.02).unsqueeze(1)
y = weight * X + bias

train_split = int(0.8 * len(X))  # 80% of data used for training set, 20% for testing
X_train, y_train = X[:train_split], y[:train_split]
X_test, y_test = X[train_split:], y[train_split:]


# Create a linear model
class LinearRegressionModel(nn.Module):
    def __init__(self, in_size: int = 1, out_size: int = 1):
        super().__init__()
        self.linear_layer = nn.Linear(in_size, out_size)

    def forward(self, x: torch.Tensor) -> torch.Tensor:
        return self.linear_layer(x)


torch.manual_seed(42)  # For reproducibility
model_0 = LinearRegressionModel()


# Train the model

loss_fn = nn.MSELoss(reduction="sum")
optimizer = torch.optim.SGD(params=model_0.parameters(), lr=0.01)
epochs = 100

train_loss_values = []
test_loss_values = []
epoch_count = []

for epoch in range(epochs):
    model_0.train()

    y_pred = model_0(X_train)
    loss = loss_fn(y_pred, y_train)
    optimizer.zero_grad()
    loss.backward()
    optimizer.step()

    model_0.eval()

    with torch.inference_mode():
        test_pred = model_0(X_test)
        test_loss = loss_fn(test_pred, y_test.type(torch.float))
        if epoch % 10 == 0:
            epoch_count.append(epoch)
            train_loss_values.append(loss.detach().numpy())
            test_loss_values.append(test_loss.detach().numpy())
            print(
                f"Epoch: {epoch} | MSE Train Loss: {loss} | MSE Test Loss: {test_loss} "
            )

# Plot the loss curves and test the model

plt.plot(epoch_count, train_loss_values, label="Train loss")
plt.plot(epoch_count, test_loss_values, label="Test loss")
plt.title("Training and test loss curves")
plt.ylabel("Loss")
plt.xlabel("Epochs")
plt.legend()

print((model_0.state_dict()))  # Check the parameters of the model
with torch.inference_mode():
    y_preds = model_0(X_test)
plot_predictions(X_train, y_train, X_test, y_test, y_preds)
