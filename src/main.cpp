#include <iostream>
#include <vector>
#include "neural_network.hpp"

int main(void) {
    NeuralNetwork Net1;

    std::vector<int> topo = {2, 4, 1};
    NeuralNetwork Net2(topo);

    for (auto& t: Net2.topology) {
        std::cout << t << "\n";
    }
}