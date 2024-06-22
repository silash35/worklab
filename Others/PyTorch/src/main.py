from matplotlib import pyplot as plt
import torch
from torch import nn
from visualize import plot_predictions
from trainer import trainer
from data_generators import linear


# Create data
X_train, y_train, X_test, y_test = linear(0.7, 0.3)

# Create a linear model
from models.linear_regression import LinearRegressionModel

torch.manual_seed(42)  # For reproducibility
model_0 = LinearRegressionModel()

# Train the model

loss_fn = nn.MSELoss(reduction="sum")
optimizer = torch.optim.SGD(params=model_0.parameters(), lr=0.01)

train_loss_values, test_loss_values, epoch_count = trainer(
    model_0, loss_fn, optimizer, X_train, y_train, X_test, y_test
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
