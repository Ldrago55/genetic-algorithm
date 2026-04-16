#include "environment.hpp"
#include "population.hpp"
#include "raylib.h"

int main() {
    // 1. Initialization
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Neuroevolution: Self-Driving Cars");
    SetTargetFPS(60);

    std::vector<int> nnTopology = {4, 6, 2};
    Environment env(screenWidth, screenHeight);
    
    int popSize = 50;
    int maxIter = 200;
    Population pop(popSize, nnTopology, maxIter);

    // Main Game Loop
    while (!WindowShouldClose()) {
        
        // 2. Logic Update
        
        // Update agents first
        pop.update(env);

        // Then check if generation is over AND we haven't reached max iterations yet
        if (pop.isGenerationOver() || pop.hasReachedMaxIterations()) {
            pop.nextGeneration();
        }


        // 3. Drawing
        BeginDrawing();
        ClearBackground(RAYWHITE);

        env.draw();
        pop.draw();

        DrawText(("Generation: " + std::to_string(pop.generation)).c_str(), 10, 10, 20, BLACK);
        DrawText(("Iteration: " + std::to_string(pop.currentIteration) + "/" + std::to_string(pop.maxIterations)).c_str(), 10, 35, 20, BLACK);
        DrawText(("Best Fitness: " + std::to_string((int)pop.bestFitness)).c_str(), 10, 60, 20, BLACK);
        
        int aliveCount = 0;
        for(const auto& a : pop.agents) {
            if(!a.isDead) aliveCount++;
        }
        DrawText(("Alive: " + std::to_string(aliveCount) + "/" + std::to_string(pop.populationSize)).c_str(), 10, 85, 20, BLACK);
        
        DrawText("Green: Alive | Red: Dead", 10, screenHeight - 30, 15, DARKGRAY);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}