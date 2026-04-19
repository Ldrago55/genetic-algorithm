#include "Agent.h"
#include "neural_network.hpp"
#include <raylib.h>


// Constructor
Agent::Agent() {
    Vector3 position = {0, 1, 0};
    NeuralNetwork brain = NeuralNetwork();
}

Agent::Agent(Vector3 pos, const NeuralNetwork& nn) {
    Vector3 position = pos;
    NeuralNetwork brain = nn;
}


Action Agent::decide(const State& state) {
    Action action;

    // Take action using NN(GA)
    


    return action;
}
