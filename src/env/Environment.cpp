#include "Environment.h"
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
    agentPos.z += action.moveX;
}

Vector3 Environment::getTarget() {
    return target;
}