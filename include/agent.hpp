#ifndef AGENT_H
#define AGENT_H

#include "neural_network.hpp"
#include <raylib.h>
#include <vector>

struct Sensor {
    Vector2 origin;
    Vector2 end;
    float distance;
    bool collided;
};

class Agent {
public:
    Vector2 position;
    Vector2 velocity;
    float angle; // In radians
    float radius;
    
    NeuralNetwork brain;
    float fitness;
    bool isDead;
    
    // Sensors for input
    std::vector<Sensor> sensors;
    int numSensors;

    Agent();
    Agent(const std::vector<int>& topology);
    
    void update();
    void draw(Color color) const;
    void think(const std::vector<float>& inputs);
    
    // Calculate fitness based on movement/survival
    void calculateFitness();
    
    // Helper to get sensor readings (to be implemented in Environment later)
    // For now, we'll simulate dummy inputs in main if environment isn't ready
    std::vector<float> getSensors() const;

private:
    void updateSensors();
};

#endif // AGENT_H