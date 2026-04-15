#include "neural_network.hpp"
#include <cstddef>
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

    
    /*Calculate total Genes needed
    For each layer connection (layer i to layer i+1):
        total_W_&_B = (input * output) + bias_of_output
    */
    int totalGenes = 0;
    for (size_t i = 0; i < topology.size() - 1; i++) {
        int inputs = topology[i];
        int outputs = topology[i + 1];
        totalGenes += (inputs * outputs) + outputs; // weights + biases
    }
    // Resize the chromosome to the no. of genes
    chromosome.resize(totalGenes, 0.0f);
    // Randomize weights & biases (Chromosome)
    randomizeChromosome();
}

// ---- Functions ----

// Randomize weights & biases (Chromosome)
void NeuralNetwork::randomizeChromosome() {
    // Initialize Uniform Real Distribution
    std::uniform_real_distribution<float> dist(-1.0f, 1.0f);
    for (auto& chr : chromosome) {
        chr = dist(rng);
    }
}

// Get Total Genes
int NeuralNetwork::getTotalGenes() const {
    int totalGenes = chromosome.size();
    return totalGenes;
}

// RELU Activation function
float NeuralNetwork::reLU(float x) {
    return (0.0f < x) ? x : 0.0f;
}