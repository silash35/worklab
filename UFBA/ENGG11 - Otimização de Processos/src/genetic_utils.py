import numpy as np

from typings import Chromosome, Fitness_func, GA_params, Individual, Population


# Inicializa a população com indivíduos aleatórios
def initialize_population(params: GA_params, fitness_func: Fitness_func) -> Population:
    population: Population = []
    for _ in range(params["pop_size"]):
        chromosome: Chromosome = np.array(
            [
                np.random.uniform(params["bounds"][0][0], params["bounds"][0][1]),
                np.random.uniform(params["bounds"][1][0], params["bounds"][1][1]),
            ],
            dtype=np.float32,
        )
        individual: Individual = {
            "chromosome": chromosome,
            "fitness": fitness_func(chromosome),
        }
        population.append(individual)

    return population


# Seleção de pais por torneio
def tournament_selection(population: Population, k=3):
    selected_indices = np.random.choice(len(population), size=k, replace=False)
    selected_individuals = [population[i] for i in selected_indices]
    best_from_selected = max(selected_individuals, key=lambda ind: ind["fitness"])
    return best_from_selected


# Cruzamento (Crossover)
def crossover(
    parent1: Individual,
    parent2: Individual,
    fitness_func: Fitness_func,
    params: GA_params,
):
    if np.random.rand() < params["crossover_rate"]:
        alpha = np.random.rand()  # Peso para a combinação linear
        child1_chromosome = (
            alpha * parent1["chromosome"] + (1 - alpha) * parent2["chromosome"]
        )
        child2_chromosome = (
            alpha * parent2["chromosome"] + (1 - alpha) * parent1["chromosome"]
        )

        child1: Individual = {
            "chromosome": child1_chromosome,
            "fitness": fitness_func(child1_chromosome),
        }
        child2: Individual = {
            "chromosome": child2_chromosome,
            "fitness": fitness_func(child2_chromosome),
        }

        return child1, child2
    else:
        return parent1, parent2


# Mutação simples (perturbação em uma variável)
def mutate(
    individual: Individual,
    fitness_func: Fitness_func,
    params: GA_params,
):
    if np.random.rand() < params["mutation_rate"]:
        gene = np.random.randint(0, 2)  # Escolhe entre Cv1 ou Cv2 para mutação

        mutation = np.random.uniform(
            -params["mutation_strength"], params["mutation_strength"]
        )
        individual["chromosome"][gene] += mutation

        individual["chromosome"][gene] = np.clip(
            individual["chromosome"][gene],
            params["bounds"][gene][0],
            params["bounds"][gene][1],
        )

        individual["fitness"] = fitness_func(individual["chromosome"])
    return individual
