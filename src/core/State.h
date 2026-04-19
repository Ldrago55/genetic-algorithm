#pragma once
#include "raylib.h"

// Defining interface between Environment -> Agent
// Environment -> gives -> State

struct State {
    Vector3 agentPos;
    Vector3 targetPos;
};