#include "environment.hpp"
#include <algorithm>
#include <cmath>

Environment::Environment(int w, int h) : width(w), height(h) {
    createBoxRoom();
}

void Environment::createBoxRoom() {
    // Define the four walls of the screen
    // Top
    addWall({0, 0}, {(float)width, 0});
    // Right
    addWall({(float)width, 0}, {(float)width, (float)height});
    // Bottom
    addWall({(float)width, (float)height}, {0, (float)height});
    // Left
    addWall({0, (float)height}, {0, 0});

    // Add some internal obstacles
    addWall({200, 200}, {200, 400});
    addWall({500, 100}, {600, 300});
    addWall({300, 500}, {700, 500});
}

void Environment::addWall(Vector2 start, Vector2 end) {
    walls.push_back({start, end});
}

void Environment::draw() const {
    // Draw Walls
    for (const auto& wall : walls) {
        DrawLineV(wall.start, wall.end, WHITE);
    }
}

void Environment::updateAgents(std::vector<Agent>& agents) {
    for (auto& agent : agents) {
        if (agent.isDead) continue;

        // 1. Update Sensors (Raycasting)
        std::vector<float> inputs;
        
        for (int i = 0; i < agent.numSensors; ++i) {
            float hitX, hitY;
            // Cast ray from sensor origin to sensor end
            float dist = castRay(agent.sensors[i].origin, agent.sensors[i].end, hitX, hitY);
            
            // Update sensor visual data
            agent.sensors[i].distance = dist;
            agent.sensors[i].collided = (dist < 100.0f); // Assume 100 is max sensor length
            
            // If collided, update the visual end point to the hit point
            if (agent.sensors[i].collided) {
                agent.sensors[i].end.x = hitX;
                agent.sensors[i].end.y = hitY;
            } else {
                // Reset end point to max length if no hit (for drawing)
                float angle = agent.angle + (i == 0 ? -0.785f : (i == 1 ? 0.0f : 0.785f));
                agent.sensors[i].end.x = agent.position.x + cos(angle) * 100.0f;
                agent.sensors[i].end.y = agent.position.y + sin(angle) * 100.0f;
            }
            
            // Normalize input: 1.0 = close/collision, 0.0 = far
            float normalizedDist = 1.0f - (dist / 100.0f);
            if (normalizedDist < 0) normalizedDist = 0;
            inputs.push_back(normalizedDist);
        }
        
        // Add 4th input: Speed
        float speed = sqrt(agent.velocity.x*agent.velocity.x + agent.velocity.y*agent.velocity.y);
        inputs.push_back(speed / 5.0f);

        // 2. Think (Neural Network)
        agent.think(inputs);

        // 3. Move
        agent.update();

        // 4. Check Death (Collision with walls)
        // Simple check: if any sensor is very close, it might be inside a wall.
        // Better check: Check if agent position is outside bounds or intersects a wall.
        // For simplicity, we'll kill if it hits the screen bounds or if a sensor detects a hit < radius
        
        bool collision = false;
        
        // Check screen bounds
        if (agent.position.x < 0 || agent.position.x > width || 
            agent.position.y < 0 || agent.position.y > height) {
            collision = true;
        }

        // Check wall intersections (simple point-circle vs line segment)
        // This is computationally expensive, so we only do it if bounds are ok
        if (!collision) {
            for (const auto& wall : walls) {
                // Distance from point (agent) to line segment (wall)
                // If distance < radius, collision
                float dist = getDistanceToSegment(agent.position, wall.start, wall.end);
                if (dist < agent.radius) {
                    collision = true;
                    break;
                }
            }
        }

        if (collision) {
            agent.isDead = true;
            agent.calculateFitness();
        }
    }
}

// Helper: Distance from point P to line segment AB
float Environment::getDistanceToSegment(Vector2 p, Vector2 a, Vector2 b) const {
    Vector2 pa = {p.x - a.x, p.y - a.y};
    Vector2 ba = {b.x - a.x, b.y - a.y};
    
    float h = std::clamp((pa.x * ba.x + pa.y * ba.y) / (ba.x * ba.x + ba.y * ba.y), 0.0f, 1.0f);
    
    Vector2 projection = {a.x + h * ba.x, a.y + h * ba.y};
    Vector2 diff = {p.x - projection.x, p.y - projection.y};
    
    return sqrt(diff.x * diff.x + diff.y * diff.y);
}

// Raycasting Logic
float Environment::castRay(Vector2 origin, Vector2 end, float& outX, float& outY) const {
    float closestDist = 100000.0f; // Large number
    bool hit = false;
    
    Line ray = {origin, end};
    
    for (const auto& wall : walls) {
        float interX, interY;
        if (getIntersection(ray, wall, interX, interY)) {
            float dist = sqrt((interX - origin.x)*(interX - origin.x) + (interY - origin.y)*(interY - origin.y));
            if (dist < closestDist) {
                closestDist = dist;
                outX = interX;
                outY = interY;
                hit = true;
            }
        }
    }
    
    if (hit) {
        return closestDist;
    } else {
        // Return max sensor length if no hit
        return 100.0f; 
    }
}

// Line-Line Intersection Algorithm
bool Environment::getIntersection(Line l1, Line l2, float& interX, float& interY) const {
    float x1 = l1.start.x, y1 = l1.start.y;
    float x2 = l1.end.x, y2 = l1.end.y;
    float x3 = l2.start.x, y3 = l2.start.y;
    float x4 = l2.end.x, y4 = l2.end.y;

    float den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
    if (den == 0) return false; // Parallel lines

    float t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / den;
    float u = -((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3)) / den;

    if (t >= 0 && t <= 1 && u >= 0 && u <= 1) {
        interX = x1 + t * (x2 - x1);
        interY = y1 + t * (y2 - y1);
        return true;
    }
    
    return false;
}