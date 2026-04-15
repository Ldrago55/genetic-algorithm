#include <iostream>
#include <vector>
#include "neural_network.hpp"

int main(void) {
    NeuralNetwork Net1;

    std::vector<int> topo = {2, 4, 1};
    NeuralNetwork Net2(topo);

    for (auto& c: Net2.chromosome) {
        std::cout << c << "  ";
    }
    std::cout << "\n";

    std::cout << "Total Genes: " << Net2.getTotalGenes() << "\n";
}