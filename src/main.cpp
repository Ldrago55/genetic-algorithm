#include <iostream>
#include <vector>
#include "neural_network.hpp"
#include "raylib.h"
#include "population/populationManager.h"
#include "env/Environment.h"

#define POPU_NUM 5

int main(void) {
    // Initialize environment
    Environment env = Environment();

    // Initialize population
    PopulationManager popu = PopulationManager(&env, POPU_NUM);

    // reset the population
    popu.reset();


    InitWindow(800, 600, "GA");

    // initialize camera
    Camera3D camera = {
        {0, 15, 15},
        {0, 0, 0},
        {0, 1, 0},
        60.0f,
        CAMERA_PERSPECTIVE
    };

    SetTargetFPS(30);

    while (!WindowShouldClose()) {
        // add camera control
        UpdateCamera(&camera, CAMERA_FIRST_PERSON);

        BeginDrawing();
        ClearBackground(WHITE);

        BeginMode3D(camera);

        // draw a plane
        DrawPlane(
            {0, 0, 0}, 
            {20, 20}, 
            GREEN
        );

        // draw target
        DrawCube(
            env.getTarget(), 
            2.0f, 2.0f, 2.0f, 
            RED
        );

        // draw agents
        for (int i = 0; i < popu.popSize; i++) {
            DrawCube(
                popu.population[i].position, 
                2.0f, 2.0f, 2.0f, 
                BLUE
            );
        }

        EndMode3D();

        EndDrawing();
    }
    return 0;
}