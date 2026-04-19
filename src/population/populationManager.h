#pragma once

#include <vector>
#include "../agent/Agent.h"
#include "../env/Environment.h"


class PopulationManager {
private:
    Environment* env;

public:
    int popSize;
    std::vector<Agent> population;

    PopulationManager(Environment* environment, int populationSize, const std::vector<int>& topo);

    void update(); // runs Simulation step
    void reset();
};