#include <raylib.h>
#include <iostream>
#include <memory>
#include "logic/SequentialSimulation.h"
#include "logic/ParallelSimulation.h"

enum GameMode {
    MENU,
    SEQUENTIAL,
    PARALLEL,
    COMPARISON
};

int main() {
    SetTraceLogLevel(LOG_ERROR);
    Color BACKGROUND_COLOR = {100, 100, 100, 255};
    const int WINDOW_WIDTH = 1200;
    const int WINDOW_HEIGHT = 800;
    const int CELL_SIZE = 25;
    const int FPS = 60;

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Simulation Game");
    SetTargetFPS(FPS);

    GameMode gameMode = MENU;
    std::unique_ptr<Simulation> simulation = nullptr;

    Rectangle sequentialButton = { (float)(WINDOW_WIDTH / 2 - 100), (float)(WINDOW_HEIGHT / 3), 200, 50 };
    Rectangle parallelButton = { (float)(WINDOW_WIDTH / 2 - 100), (float)(WINDOW_HEIGHT / 2), 200, 50 };
    Rectangle comparisonButton = { (float)(WINDOW_WIDTH / 2 - 100), (float)(WINDOW_HEIGHT * 2 / 3), 200, 50 };

    while (!WindowShouldClose()) {

        if (gameMode == MENU) {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                Vector2 mousePosition = GetMousePosition();
                if (CheckCollisionPointRec(mousePosition, sequentialButton)) {
                    gameMode = SEQUENTIAL;
                    simulation = std::make_unique<SequentialSimulation>(WINDOW_WIDTH, WINDOW_HEIGHT, CELL_SIZE);
                    WaitTime(0.1);
                } else if (CheckCollisionPointRec(mousePosition, parallelButton)) {
                    gameMode = PARALLEL;
                    simulation = std::make_unique<ParallelSimulation>(WINDOW_WIDTH, WINDOW_HEIGHT, CELL_SIZE);
                    WaitTime(0.1);
                } else if (CheckCollisionPointRec(mousePosition, comparisonButton)) {
                    gameMode = COMPARISON;
                    WaitTime(0.1);
                }
            }


            BeginDrawing();
            ClearBackground(BACKGROUND_COLOR);

            DrawText("Choose a Simulation Mode", 400, 100, 30, BLACK);

            DrawRectangleRec(sequentialButton, DARKGRAY);
            DrawText("Play Sequential", (int)(sequentialButton.x + 50), (int)(sequentialButton.y + 15), 20, WHITE);

            DrawRectangleRec(parallelButton, DARKGRAY);
            DrawText("Play Parallel", (int)(parallelButton.x + 50), (int)(parallelButton.y + 15), 20, WHITE);

            DrawRectangleRec(comparisonButton, DARKGRAY);
            DrawText("Comparison", (int)(comparisonButton.x + 50), (int)(comparisonButton.y + 15), 20, WHITE);

            EndDrawing();
        }


        if (gameMode == SEQUENTIAL || gameMode == PARALLEL) {

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                Vector2 mousePosition = GetMousePosition();
                int row = mousePosition.y / CELL_SIZE;
                int column = mousePosition.x / CELL_SIZE;
                simulation->toggleCell(row, column);
            }

            if (IsKeyPressed(KEY_ENTER)) {
                simulation->start();
                SetWindowTitle("Simulation Started");
            } else if (IsKeyPressed(KEY_SPACE)) {
                simulation->stop();
                SetWindowTitle("Simulation Stopped");
            } else if (IsKeyPressed(KEY_R)) {
                simulation->createRandomState();
            } else if (IsKeyPressed(KEY_C)) {
                simulation->clearGrid();
            }

            simulation->update();

            BeginDrawing();
            ClearBackground(BACKGROUND_COLOR);
            simulation->draw();
            EndDrawing();
        }

        if (gameMode == COMPARISON) {
            // TODO
            BeginDrawing();
            ClearBackground(BACKGROUND_COLOR);
            DrawText("Comparison Mode (Not Implemented)", 400, 100, 30, BLACK);
            EndDrawing();
        }
    }

    CloseWindow();
    return 0;
}
