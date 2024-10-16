import numpy as np


# Cruzamento (Crossover) simples
def crossover(parent1, parent2, crossover_rate=0.8):
    if np.random.rand() < crossover_rate:
        alpha = np.random.rand()  # Peso para a combinação linear
        child1 = alpha * parent1 + (1 - alpha) * parent2
        child2 = alpha * parent2 + (1 - alpha) * parent1
        return child1, child2
    else:
        return parent1, parent2


# Mutação simples (perturbação em uma variável)
def mutate(individual, mutation_rate=0.1, mutation_strength=0.1):
    if np.random.rand() < mutation_rate:
        idx = np.random.randint(0, 2)  # Escolhe entre x ou y para mutação
        individual[idx] += np.random.uniform(-mutation_strength, mutation_strength)
    return individual
