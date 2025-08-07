import os
import time
from typing import Any, Callable

import hickle as hkl
import torch


def test_train_speed(
    train_fn: Callable[[torch.nn.Module, int], Any],
    getModel: Callable[[], torch.nn.Module],
    n_execuções: int,
    results_path: str,
    model_path: str,
):
    times = []
    returns = []
    model = getModel()

    if os.path.exists(results_path) and os.path.exists(model_path):
        print("Recuperando testes anteriores")
        times, returns = hkl.load(results_path)
        model.load_state_dict(torch.load(model_path, weights_only=True))
    else:
        print("Fazendo testes")
        for i in range(n_execuções):
            torch.manual_seed(i)
            model = getModel()
            start_time = time.time()
            result = train_fn(model, i)
            end_time = time.time()
            times.append(end_time - start_time)
            returns.append(result)

        print("Salvando para futuras execuções")
        hkl.dump((times, returns), results_path)
        model.eval()
        torch.save(model.state_dict(), model_path)

    return (
        times,
        returns,
        model,
    )
