import os
from typing import Callable

import hickle as hkl
import optuna


def study(
    objective: Callable,
    trials: int,
    study_name: str,
    study_path: str,
    study_direction="minimize",
    print_results=True,
):
    study = optuna.create_study(direction=study_direction, study_name=study_name)

    if os.path.exists(study_path):
        print("Otimização realizada anteriormente. Recuperando valores...")
        study = hkl.load(study_path)
    else:
        print(f"Otimizando hiperparâmetros do estudo '{study_name}'")
        study.optimize(objective, n_trials=trials)
        print("Salvando estudo para futuras execuções")
        hkl.dump(study, study_path)

    best_study = study.best_trial

    if print_results:
        print("Imprimindo resultado:")
        print("  Valor do Loss:", best_study.value)

        print("  hiperparâmetros:")
        for key, value in best_study.params.items():
            print(f"    {key}: {value}")

    return best_study.params
