from matplotlib import pyplot as plt
import torch
from torch import nn
from trainer import trainer
from data_generators import blobs

torch.manual_seed(42)  # For reproducibility

# Create data
X_train, X_test, y_train, y_test = blobs(2, 4)

# Create a linear model
from models.blob import BlobModel

model = BlobModel(2, 4)

# Train the model

loss_fn = nn.CrossEntropyLoss()
optimizer = torch.optim.SGD(model.parameters(), lr=0.1)

train_loss_values, test_loss_values, epoch_count = trainer(
    model, loss_fn, optimizer, X_train, y_train, X_test, y_test, 100, False
)


# Test the model


def accuracy_fn(y_true: torch.Tensor, y_pred: torch.Tensor) -> float:
    correct = torch.eq(y_true, y_pred).sum().item()
    acc = (correct / len(y_pred)) * 100
    return acc


y_preds = []
with torch.inference_mode():
    y_preds_probs = model(X_test)
    y_preds = y_preds_probs.argmax(dim=1)


print(f"Predictions: {y_preds[:10]}\nLabels     : {y_test[:10]}")
print(f"Test accuracy: {accuracy_fn(y_test, y_preds)}%")
