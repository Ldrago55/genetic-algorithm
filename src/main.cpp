#include "raylib.h"
#include "agent.hpp"

int main() {
    InitWindow(800, 600, "Agent Test");
    SetTargetFPS(60);

    Agent agent;

    while (!WindowShouldClose()) {
        // Think and update
        agent.think(agent.getSensors());
        agent.update();

        // Draw
        BeginDrawing();
        ClearBackground(BLACK);
        agent.draw(BLUE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
