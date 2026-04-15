#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H

#include <random>
#include <vector>

class NeuralNetwork {
public:
    // Architecture: ex: {4, 6, 2}    4 inp -> 6 hidden -> 2 output
    std::vector<int> topology;

    // All weights & biases stored in a flat vector
    std::vector<float> chromosome;


    // Constructors
    NeuralNetwork();
    NeuralNetwork(const std::vector<int>& topology);

    // ---- Functions ----

    // Randomize weights & biases (Chromosome)
    void randomizeChromosome();
    // Get total Genes
    int getTotalGenes() const; // will NOT modify the object

private:
    std::mt19937 rng;
    // ---- Functions ----
    // RELU Activation function
    float reLU(float x);
};

#endif