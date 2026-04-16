#include "population.hpp"
#include <algorithm>
#include <iostream>

Population::Population(int size, const std::vector<int>& nnTopology) 
    : populationSize(size), generation(1), bestFitness(0), maxSteps(1000), 
      mutationRate(0.1f), mutationStrength(0.5f), elitismCount(2),
      rng(std::random_device{}()) {
    
    // Initialize agents
    for (int i = 0; i < populationSize; ++i) {
        agents.emplace_back(nnTopology);
        // Randomize start position slightly to avoid identical behavior
        agents[i].position.x = 100.0f;
        agents[i].position.y = 100.0f + (i * 5.0f); 
        agents[i].angle = 0.0f;
    }
}

void Population::update(Environment& env) {
    // Update all agents in the environment
    env.updateAgents(agents);
    
    // Track best fitness in current generation
    for (const auto& agent : agents) {
        if (agent.fitness > bestFitness) {
            bestFitness = agent.fitness;
        }
    }
}

void Population::draw() const {
    for (const auto& agent : agents) {
        // Draw alive agents in Green, dead in Red
        Color c = agent.isDead ? Color{200, 50, 50, 100} : Color{50, 200, 50, 255};
        agent.draw(c);
    }
}

bool Population::isGenerationOver() const {
    // Generation ends if all agents are dead
    for (const auto& agent : agents) {
        if (!agent.isDead) return false;
    }
    return true;
}

void Population::nextGeneration() {
    std::cout << "Generation: " << generation 
              << " | Best Fitness: " << bestFitness << std::endl;

    // 1. Sort agents by fitness (descending)
    sortAgentsByFitness();

    // 2. Create new population vector
    std::vector<Agent> newAgents;
    newAgents.reserve(populationSize);

    // 3. Elitism: Copy top N agents directly
    for (int i = 0; i < elitismCount; ++i) {
        Agent elite = agents[i];
        elite.isDead = false;
        elite.fitness = 0;
        elite.position = {100.0f, 100.0f + (i * 5.0f)}; // Reset position
        elite.velocity = {0, 0};
        elite.angle = 0;
        // Reset sensors
        for(auto& s : elite.sensors) {
            s.collided = false;
            s.distance = 100.0f;
        }
        newAgents.push_back(elite);
    }

    // 4. Fill the rest with offspring
    while (static_cast<int>(newAgents.size()) < populationSize) {
        // Select two parents
        Agent parentA = selectParent();
        Agent parentB = selectParent();

        // Crossover
        Agent child(parentA.brain.topology);
        child.brain = NeuralNetwork::crossover(parentA.brain, parentB.brain);
        
        // Mutate
        child.brain.mutate(mutationRate, mutationStrength);
        
        // Reset physical state
        child.isDead = false;
        child.fitness = 0;
        child.position = {100.0f, 100.0f + (newAgents.size() * 5.0f)};
        child.velocity = {0, 0};
        child.angle = 0;
        
        // Reset sensors
        for(auto& s : child.sensors) {
            s.collided = false;
            s.distance = 100.0f;
        }

        newAgents.push_back(child);
    }

    // 5. Replace old population
    agents = std::move(newAgents);
    
    // 6. Increment generation
    generation++;
    bestFitness = 0; // Reset for next gen tracking
}

// Tournament Selection
Agent Population::selectParent() {
    std::uniform_int_distribution<int> dist(0, populationSize - 1);
    
    // Pick K random agents
    int k = 5; 
    int bestIndex = -1;
    float bestFit = -1;

    for (int i = 0; i < k; ++i) {
        int idx = dist(rng);
        if (agents[idx].fitness > bestFit) {
            bestFit = agents[idx].fitness;
            bestIndex = idx;
        }
    }

    return agents[bestIndex];
}

void Population::sortAgentsByFitness() {
    std::sort(agents.begin(), agents.end(), [](const Agent& a, const Agent& b) {
        return a.fitness > b.fitness;
    });
}