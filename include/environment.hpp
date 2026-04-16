#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <raylib.h>
#include <vector>
#include "agent.hpp"

struct Line {
    Vector2 start;
    Vector2 end;
};

class Environment {
public:
    int width;
    int height;
    std::vector<Line> walls;

    Environment(int w, int h);
    
    // Add a wall (line segment)
    void addWall(Vector2 start, Vector2 end);
    
    // Create a default box room
    void createBoxRoom();

    // Update all agents: handle sensors, collisions, and movement
    void updateAgents(std::vector<Agent>& agents);

    // Draw the environment
    void draw() const;

private:
    // Raycast a single sensor against all walls
    // Returns distance to closest hit, or maxDist if no hit
    float castRay(Vector2 origin, Vector2 end, float& outX, float& outY) const;
    
    // Check if two line segments intersect
    // Returns true if they intersect, and sets interX/interY to the point
    bool getIntersection(Line l1, Line l2, float& interX, float& interY) const;

    float getDistanceToSegment(Vector2 p, Vector2 a, Vector2 b) const ;
};

#endif // ENVIRONMENT_H