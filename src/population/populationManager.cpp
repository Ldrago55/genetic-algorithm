#include "populationManager.h"
#include "neural_network.hpp"
#include <algorithm>
#include <cstdlib>
#include <vector>

PopulationManager::PopulationManager(Environment* environment, int populationSize, const std::vector<int>& topo) {
    env = environment;
    popSize = populationSize;

    population.resize(populationSize);
    for (auto& agent : population) {
        agent.brain = NeuralNetwork(topo);
    }
}

void PopulationManager::update() {
    for (int i = 0; i < popSize; i++) {
        // get state from environment
        State s = env->getState(population[i].position);

        // agent decides action based on state
        Action a = population[i].decide(s);

        // environment applies movement
        env->applyAction(population[i].position, a);

        // calculate fitness of agent
        population[i].fitness = env->calculateFitness(population[i].position);

    }
}

void PopulationManager::reset() {
    // init every agent with i, 1, 0 position
    for (int i = 0; i < popSize; i++) {
        population[i].position = {-10, 1, 0};
    }
}

void PopulationManager::evolve() {
    // sort by fitness(high to low)
    std::sort(population.begin(), population.end(),
        [](const Agent& a, const Agent& b) {
            return a.fitness > b.fitness;
        });

    // push best fitness agent to new population
    std::vector<Agent> newPopulation;
    newPopulation.push_back(population[0]);

    // generate rest of the new population
    for (int i = 0; i < popSize; i++) {
        // select parent from top 50% gene pool
        Agent& parentA = population[rand() % (popSize / 2)];
        Agent& parentB = population[rand() % (popSize / 2)];

        Agent child;

        // crossover
        child.brain = NeuralNetwork::crossover(parentA.brain, parentB.brain);

        // mutate
        child.brain.mutate(0.1f, 0.5f);

        // push the child to new population
        newPopulation.push_back(child);
    }

    // set population to new population
    population = newPopulation;
}
