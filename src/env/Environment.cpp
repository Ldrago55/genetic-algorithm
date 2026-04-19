#include "Environment.h"
#include <cmath>
#include <raylib.h>

Environment::Environment() {
    target = {7, 1, 0};
}

State Environment::getState(const Vector3& agentPos) {
    State state;
    state.agentPos = agentPos;
    state.targetPos = target;
    return state;
}

void Environment::applyAction(Vector3& agentPos, Action& action) {
    // apply the action to agent
    agentPos.x += action.moveX;  // modifying agent position
    agentPos.z += action.moveZ;
}

Vector3 Environment::getTarget() {
    return target;
}

float Environment::calculateFitness(Vector3& agentPos) {
    float distance = - std::sqrt(
        pow((agentPos.x - target.x), 2) +
        pow((agentPos.y - target.y), 2) +
        pow((agentPos.z - target.z), 2)
    );

    return distance;
}