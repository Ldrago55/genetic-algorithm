#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H

#include <random>
#include <vector>

class NeuralNetwork {
public:
    // Architecture: ex: {4, 6, 2}    4 inp -> 6 hidden -> 2 output
    std::vector<int> topology;

    /* All weights & biases stored in a flat vector
    6*[4w, 1b]  + 2*[6w, 1b]
        30    +     14   = 44 -> total size
    */
    std::vector<float> chromosome;

    /*Cache for layer outputs during forward pass -- for {4, 6, 2}
        [
            [_, _, _, _],
            [_, _, _, _, _, _],
            [_, _]
        ]          */
    std::vector<std::vector<float>> layers;


    // Constructors
    NeuralNetwork();
    NeuralNetwork(const std::vector<int>& topology);

    // ---- Functions ----

    // Forward Pass
    std::vector<float> feedForward(const std::vector<float>& inputs);

    // Randomize weights & biases (Chromosome)
    void randomizeChromosome();
    // Get total Genes
    int getTotalGenes() const; // will NOT modify the object

private:
    std::mt19937 rng;
    // ---- Functions ----
    // RELU Activation function
    float reLU(float x);
    // TanH Activation function
    float tanhActivation(float x);
};

#endif