#include "neural_network.hpp"
#include <cmath>
#include <cstddef>
#include <iostream>
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


    // Initialize layers cache
    for (int size : topology) {
        layers.push_back(std::vector<float>(size, 0.0f));
    }

    
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

// Forward Pass
std::vector<float> NeuralNetwork::feedForward(const std::vector<float>& inputs) {
    if ((int)inputs.size() != topology[0]) {
        std::cerr << "Error: Input size mismatch!" << std::endl;
        return {};
    }
    
    // Set input layer
    layers[0] = inputs;

    int chromosomeIdx = 0;

    // Iterate through each layer connection
    for (size_t i = 0; i < topology.size() - 1; i++) {
        // get no. of input & output neurons
        int nInputs = topology[i];
        int nOutputs = topology[i+1];

        // For each neuron in the next layer
        for (int j = 0; j < nOutputs; j++) {
            // Calculate sum(for 1 neuron) = (inputs * weights) + bias
            // Initialize sum = 0
            float sum = 0.0f;

            for (int k = 0; k < nInputs; k++) {
                // sum += layer[inp_layer][k_iterates] * chromosome[weight_idx]
                // for more info, refer to `chromosome` variable in .hpp file
                sum += layers[i][k] * chromosome[chromosomeIdx];
                chromosomeIdx++;
            }
            // Add bias to sum
            sum += chromosome[chromosomeIdx];
            chromosomeIdx++;

            // Apply activation function & store in layers[next_layer][j_iterates]
            // (bias added based on hidden<relu> & output<tanh>)
            if (i < topology.size() - 2) {
                layers[i+1][j] = reLU(sum);
            } else {
                layers[i+1][j] = tanhActivation(sum);
            }
        }
    }

    // Return the Output layer
    return layers.back(); //The last element (output_layer)
}

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

// Mutate the chromosome
void NeuralNetwork::mutate(float mutationRate, float mutationStrength) {
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);
    std::normal_distribution<float> normalDist(0.0f, mutationStrength);

    for (auto& gene: chromosome) {
        if (dist(rng) < mutationRate) {
            // Add Gaussian/Normal noise to the Gene
            gene += normalDist(rng);
        }
    }
}


// Crossover 2 chromosome
NeuralNetwork NeuralNetwork::crossover(const NeuralNetwork& parentA, const NeuralNetwork& parentB) {
    // Uniform int distribution [0, 1]
    std::uniform_int_distribution<int> dist(0, 1);

    // Construct child NN with any parent's topology
    NeuralNetwork child(parentA.topology);

    // Uniform crossover: for each gene, randomly pick from parentA or parentB
    for (int i = 0; i < parentA.getTotalGenes(); i++) {
        if (dist(child.rng) == 0) {
            child.chromosome[i] = parentA.chromosome[i];
        } else {
            child.chromosome[i] = parentB.chromosome[i];
        }
    }

    return child;
}

// RELU Activation function
float NeuralNetwork::reLU(float x) {
    return (0.0f < x) ? x : 0.0f;
}

// TanH activation function
float NeuralNetwork::tanhActivation(float x) {
    return std::tanh(x);
}