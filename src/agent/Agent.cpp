#include "Agent.h"
#include <raylib.h>


// Constructor
Agent::Agent() {
    Vector3 position = {0, 1, 0};
}

Agent::Agent(Vector3 pos) {
    Vector3 position = pos;
}


Action Agent::decide(const State& state) {
    Action action;

    // Random movement (-1 to 1)
    action.moveX = GetRandomValue(-100, 100) / 100.0f;
    action.moveZ = GetRandomValue(-100, 100) / 100.0f;

    return action;
}
