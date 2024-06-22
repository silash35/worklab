import torch
import matplotlib.pyplot as plt
from typing import Optional


def plot_predictions(
    train_X: torch.Tensor,
    train_Y: torch.Tensor,
    test_X: torch.Tensor,
    test_Y: torch.Tensor,
    predictions: Optional[torch.Tensor] = None,
):
    """
    Plots training data, test data and compares predictions.
    """
    plt.figure(figsize=(10, 7))

    # Plot training data in blue
    plt.scatter(train_X, train_Y, c="b", s=4, label="Training data")

    # Plot test data in green
    plt.scatter(test_X, test_Y, c="g", s=4, label="Testing data")

    if predictions is not None:
        # Plot the predictions in red (predictions were made on the test data)
        plt.scatter(test_X, predictions, c="r", s=4, label="Predictions")

    # Show the legend
    plt.legend(prop={"size": 14})
    plt.show()
