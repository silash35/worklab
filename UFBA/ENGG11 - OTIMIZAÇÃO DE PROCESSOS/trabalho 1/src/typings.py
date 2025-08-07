from typing import Callable, TypedDict

import numpy as np
from numpy.typing import NDArray

Chromosome = NDArray[np.float32]


class Individual(TypedDict):
    chromosome: Chromosome
    fitness: float


type Population = list[Individual]


Bounds = list[tuple[float, float]]


class GA_params(TypedDict):
    pop_size: int
    num_generations: int
    mutation_rate: float
    mutation_strength: float
    crossover_rate: float
    bounds: Bounds


type Fitness_func = Callable[[Chromosome], float]
