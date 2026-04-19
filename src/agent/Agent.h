#pragma once

#include "../core/State.h"
#include "../core/Action.h"
#include "neural_network.hpp"
#include <raylib.h>

class Agent {
public:
    Vector3 position;
    NeuralNetwork brain;

    Agent();
    Agent(Vector3 pos, const NeuralNetwork& nn);

    // Core decision making funcion
    Action decide(const State& state);
};