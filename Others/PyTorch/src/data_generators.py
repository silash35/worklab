import numpy as np
import torch
from typing import cast


def linear(weight, bias):
    X = torch.arange(start=0, end=1, step=0.02).unsqueeze(1)
    y = weight * X + bias

    return train_test_split(X, y, test_size=0.2, random_state=42)


from sklearn.datasets import make_blobs
from sklearn.model_selection import train_test_split


def blobs(n_features: int, n_classes: int):
    blob_data = cast(
        tuple[np.ndarray[np.float64, np.float64], np.ndarray[np.int64]],  # type: ignore
        make_blobs(
            n_samples=1000,
            n_features=n_features,
            centers=n_classes,
            cluster_std=1.5,
            random_state=42,
        ),
    )

    X_blob = torch.from_numpy(blob_data[0]).type(torch.float32)
    y_blob = torch.from_numpy(blob_data[1]).type(torch.int64)

    return train_test_split(X_blob, y_blob, test_size=0.2, random_state=42)
