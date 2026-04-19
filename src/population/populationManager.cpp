#include "populationManager.h"
#include "neural_network.hpp"

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
    }
}

void PopulationManager::reset() {
    // init every agent with i, 1, 0 position
    for (int i = 0; i < popSize; i++) {
        population[i].position = {(float)i, 1, 0};
    }
}
