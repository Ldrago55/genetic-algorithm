#include "neural_network.hpp"
#include <random>
#include <vector>


// Default Constructor (empty)
NeuralNetwork::NeuralNetwork() {
    std::random_device rd; // get seed from OS entropy
    rng.seed(rd()); // initialize the rng with seed
};

// Parameterized Constructor (Initializes with topology)
NeuralNetwork::NeuralNetwork(const std::vector<int>& topo) {
    topology = topo;

    // Initialize random number generator
    std::random_device rd; 
    rng.seed(rd());
}
