#pragma once

#include "../core/State.h"
#include "../core/Action.h"
#include <raylib.h>

class Agent {
public:
    Vector3 position;

    Agent();
    Agent(Vector3 pos);

    // Core decision making funcion
    Action decide(const State& state);
};