#include "raylib.h"
#include "agent.hpp"
#include "environment.hpp"
#include <vector>

int main() {
    InitWindow(800, 600, "Agent Environment Test");
    SetTargetFPS(60);

    Environment env(800, 600);
    std::vector<Agent> agents;

    // Create 3 test agents
    for (int i = 0; i < 3; ++i) {
        Agent a;
        a.position.x = 100 + i * 200;
        a.position.y = 100;
        agents.push_back(a);
    }

    while (!WindowShouldClose()) {
        // Update environment and agents
        env.updateAgents(agents);

        // Draw
        BeginDrawing();
        ClearBackground(BLACK);
        env.draw();
        
        for (auto& agent : agents) {
            agent.draw(BLUE);
        }

        // Draw UI
        int aliveCount = 0;
        for (const auto& a : agents) {
            if (!a.isDead) aliveCount++;
        }
        DrawText(TextFormat("Alive: %d/%d", aliveCount, (int)agents.size()), 10, 10, 20, WHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
