#include "Agent.h"
#include <raylib.h>
#include <vector>


// Constructor
Agent::Agent() {
    position = {0, 1, 0};
    NeuralNetwork brain = NeuralNetwork();
    fitness = 0;
}

Agent::Agent(Vector3 pos, const NeuralNetwork& nn) {
    position = pos;
    NeuralNetwork brain = nn;
    fitness = 0;
}


Action Agent::decide(const State& state) {
    Action action;

    // convert state into usable form (straight 1D array)
    std::vector<float> s = {
        state.agentPos.x, 
        state.agentPos.y, 
        state.agentPos.z, 
        state.targetPos.x,
        state.targetPos.y,
        state.targetPos.z,
    };

    // Take action using NN(GA)
    std::vector<float> output = brain.feedForward(s);
    // std::cout << output[0] << " " << output[1] << "\n";

    // assign output to action
    action.moveX = output[0];
    action.moveZ = output[1];

    return action;
}
