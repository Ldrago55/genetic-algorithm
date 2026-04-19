#include <iostream>
#include <vector>
#include "neural_network.hpp"
#include "raylib.h"

int main(void) {
    InitWindow(800, 600, "GA");

    // initialize camera
    Camera3D camera = {
        {0, 2, 10},
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
            {10, 10}, 
            GREEN
        );

        // draw a cube
        DrawCube(
            {0, 0, 0}, 
            2.0f, 2.0f, 2.0f, 
            RED
        );

        EndMode3D();

        EndDrawing();
    }
    return 0;
}