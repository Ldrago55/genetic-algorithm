#include "agent.hpp"
#include "raylib.h"

// Constructor with specific topology
Agent::Agent(const std::vector<int>& topology) 
    : position({0, 0}), velocity({0, 0}), angle(0), radius(10), 
      brain(topology), fitness(0), isDead(false), numSensors(3) {
    
    // Initialize sensors (offsets relative to agent)
    // We will update their absolute positions in updateSensors()
    sensors.resize(numSensors);
}

// Default constructor
Agent::Agent() : Agent({4, 6, 2}) {} // Default topology: 4 inputs, 6 hidden, 2 outputs

void Agent::update() {
    if (isDead) return;

    // Update physics
    position.x += velocity.x;
    position.y += velocity.y;

    // Friction/Damping
    velocity.x *= 0.95f;
    velocity.y *= 0.95f;

    // Update sensor positions based on new agent position/angle
    updateSensors();
    
    // Increment fitness simply by staying alive
    fitness += 1.0f;
}

void Agent::draw(Color color) const {
    if (isDead) {
        DrawCircleV(position, radius, ColorAlpha(color, 0.3f));
        return;
    }

    // Draw Body
    DrawCircleV(position, radius, color);
    
    // Draw Direction Indicator (Line showing where it's facing)
    Vector2 front;
    front.x = position.x + cos(angle) * radius * 1.5f;
    front.y = position.y + sin(angle) * radius * 1.5f;
    DrawLineV(position, front, WHITE);

    // Draw Sensors
    for (const auto& s : sensors) {
        Color c = s.collided ? RED : GREEN;
        DrawLineV(s.origin, s.end, c);
        DrawCircleV(s.end, 2, c);
    }
}

void Agent::think(const std::vector<float>& inputs) {
    if (isDead) return;

    // Feed inputs through neural network
    std::vector<float> outputs = brain.feedForward(inputs);

    // Output 0: Steering (-1 to 1)
    // Output 1: Acceleration (-1 to 1)
    
    float steer = outputs[0]; 
    float accel = outputs[1];

    // Update Angle
    angle += steer * 0.1f; // Max turn rate

    // Update Velocity based on angle and acceleration
    velocity.x += cos(angle) * accel * 0.5f;
    velocity.y += sin(angle) * accel * 0.5f;
    
    // Clamp speed
    float speed = sqrt(velocity.x*velocity.x + velocity.y*velocity.y);
    if (speed > 5.0f) {
        velocity.x = (velocity.x / speed) * 5.0f;
        velocity.y = (velocity.y / speed) * 5.0f;
    }
}

// Dummy sensor logic for now. 
// In a real environment, these would raycast against walls.
std::vector<float> Agent::getSensors() const {
    std::vector<float> inputs;
    for (const auto& s : sensors) {
        // Normalize distance: 1.0 means close/collision, 0.0 means far away
        // For now, just return dummy data if no environment is present
        // We will replace this with real raycasting in Environment class
        float dist = s.distance; 
        // Map distance to 0-1 range (assuming max sensor length 100)
        float normalized = 1.0f - (dist / 100.0f);
        if (normalized < 0) normalized = 0;
        inputs.push_back(normalized);
    }
    
    // Add a bias input or angle to target if needed
    // For now, let's add a 4th input: current speed normalized
    float speed = sqrt(velocity.x*velocity.x + velocity.y*velocity.y);
    inputs.push_back(speed / 5.0f);

    return inputs;
}

void Agent::calculateFitness() {
    // Fitness is already incremented in update()
    // We can add bonuses here later (e.g., reaching goal)
}

void Agent::updateSensors() {
    // Define sensor angles relative to agent heading
    // -45 deg, 0 deg, +45 deg
    float sensorLength = 100.0f;
    std::vector<float> sensorAngles = { -0.785f, 0.0f, 0.785f }; // Radians

    for (int i = 0; i < numSensors; ++i) {
        float globalAngle = angle + sensorAngles[i];
        
        sensors[i].origin = position;
        sensors[i].end.x = position.x + cos(globalAngle) * sensorLength;
        sensors[i].end.y = position.y + sin(globalAngle) * sensorLength;
        
        // Default: No collision, max distance
        sensors[i].distance = sensorLength;
        sensors[i].collided = false;
        
        // NOTE: Real collision detection happens in Environment::update()
        // Here we just set up the geometry.
    }
}