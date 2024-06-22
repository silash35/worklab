import torch


def linear(weight, bias):
    X = torch.arange(start=0, end=1, step=0.02).unsqueeze(1)
    y = weight * X + bias

    train_split = int(
        0.8 * len(X)
    )  # 80% of data used for training set, 20% for testing
    X_train, y_train = X[:train_split], y[:train_split]
    X_test, y_test = X[train_split:], y[train_split:]

    return X_train, y_train, X_test, y_test
