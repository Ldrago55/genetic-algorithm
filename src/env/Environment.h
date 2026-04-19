#pragma once

#include <raylib.h>
#include "../core/State.h"
#include "../core/Action.h"

class Environment {
private:
    Vector3 target;

public:
    Environment();

    State getState(const Vector3& agentPos);
    void applyAction(Vector3& agentPos, Action& action);

    Vector3 getTarget();
};