#include "neural_network.hpp"
#include <vector>


// Default Constructor (empty)
NeuralNetwork::NeuralNetwork() {};
// Parameterized Constructor (Initializes with topology)
NeuralNetwork::NeuralNetwork(const std::vector<int>& topo) {
    topology = topo;
}
