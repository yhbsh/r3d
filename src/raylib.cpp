#include "raylib.h"

int main(void) {
    SetTraceLogLevel(LOG_NONE);

    InitWindow(800, 600, "OBJ Model Loader");
    Camera camera = {{4.0f, 4.0f, 4.0f}, {0.0f, 1.5f, 0.0f}, {0.0f, 1.0f, 0.0f}, 45.0f, CAMERA_PERSPECTIVE};

    Model model = LoadModel("assets/penger.obj");

    SetTargetFPS(180);

    while (!WindowShouldClose()) {
        UpdateCamera(&camera, CAMERA_ORBITAL);

        BeginDrawing();
        {
            ClearBackground(RAYWHITE);
            BeginMode3D(camera);
            DrawModel(model, (Vector3){0.0f, 0.0f, 0.0f}, 1.0f, WHITE);
            DrawGrid(10, 1.0f);
            EndMode3D();
            DrawFPS(10, 10);
        }
        EndDrawing();
    }

    UnloadModel(model);
    CloseWindow();
    return 0;
}
