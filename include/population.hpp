#ifndef POPULATION_H
#define POPULATION_H

#include <vector>
#include "agent.hpp"
#include "environment.hpp"
#include <random>

class Population {
public:
    std::vector<Agent> agents;
    int populationSize;
    int generation;
    float bestFitness;
    float maxSteps; // Max steps per generation to prevent infinite loops

    int maxIterations;  // Maximum iteration allowed
    int currentIteration;  // Current iteration count
    
    // GA Parameters
    float mutationRate;
    float mutationStrength;
    int elitismCount; // Number of top agents to carry over directly

    Population(int size, const std::vector<int>& nnTopology, int maxIter);
    
    void update(Environment& env);
    void draw() const;
    
    // Check if generation is over
    bool isGenerationOver() const;
    
    // Create next generation
    void nextGeneration();

    bool hasReachedMaxIterations() const;

private:
    std::mt19937 rng;
    
    // GA Helpers
    Agent selectParent();
    void sortAgentsByFitness();
};

#endif // POPULATION_H