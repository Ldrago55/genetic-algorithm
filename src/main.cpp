#include <iostream>
#include <vector>
#include "neural_network.hpp"

int main(void) {

    std::vector<int> topo = {2, 4, 1};
    NeuralNetwork Net1(topo);
    NeuralNetwork Net2(topo);

    std::cout << "Net 1:  ";
    for (auto& c: Net1.chromosome) {
        std::cout << c << "  ";
    }
    std::cout << "\n";

    std::cout << "Net 2:  ";
    for (auto& c: Net2.chromosome) {
        std::cout << c << "  ";
    }
    std::cout << "\n";

    std::cout << "Total Genes: " << Net2.getTotalGenes() << "\n";

    // std::vector<float> inputs = {3, 4};
    // std::vector<float> outputs = Net2.feedForward(inputs);
    // std::cout << "Output: ";
    // for (auto& o: outputs) {
    //     std::cout << o << "  ";
    // }
    // std::cout << "\n";

    NeuralNetwork child = NeuralNetwork::crossover(Net1, Net2);
    std::cout << "Child:  ";
    for (auto& c: child.chromosome) {
        std::cout << c << "  ";
    }
    std::cout << "\n";

    child.mutate(0.1, 0.5);
    std::cout << "Child:  ";
    for (auto& c: child.chromosome) {
        std::cout << c << "  ";
    }
    std::cout << "\n";

}