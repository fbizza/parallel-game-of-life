#include <raylib.h>
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
    const int CELL_SIZE = 5;
    const int FPS = 90;

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Simulation Game");
    SetTargetFPS(FPS);

    GameMode gameMode = MENU;
    std::unique_ptr<Simulation> simulation = nullptr;

    Rectangle sequentialButton = {WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 3, 200, 50};
    Rectangle parallelButton = {WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2, 200, 50};
    Rectangle comparisonButton = {WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT * 2 / 3, 200, 50};

    while (!WindowShouldClose()) {
        Vector2 mousePosition = GetMousePosition();

        if (gameMode == MENU) {
            if (CheckCollisionPointRec(mousePosition, sequentialButton) ||
                CheckCollisionPointRec(mousePosition, parallelButton) ||
                CheckCollisionPointRec(mousePosition, comparisonButton)) {
                SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
            } else {
                SetMouseCursor(MOUSE_CURSOR_DEFAULT);
            }

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                SetMouseCursor(MOUSE_CURSOR_DEFAULT); //TODO: pensa a dove metterlo
                if (CheckCollisionPointRec(mousePosition, sequentialButton)) {
                    gameMode = SEQUENTIAL;
                    simulation = std::make_unique<SequentialSimulation>(WINDOW_WIDTH, WINDOW_HEIGHT, CELL_SIZE);
                } else if (CheckCollisionPointRec(mousePosition, parallelButton)) {
                    gameMode = PARALLEL;
                    simulation = std::make_unique<ParallelSimulation>(WINDOW_WIDTH, WINDOW_HEIGHT, CELL_SIZE);
                } else if (CheckCollisionPointRec(mousePosition, comparisonButton)) {
                    gameMode = COMPARISON;
                }
            }

            BeginDrawing();

            ClearBackground(BACKGROUND_COLOR);

            DrawText("Choose a Simulation Mode", 400, 100, 30, BLACK);

            DrawRectangleRec(sequentialButton, DARKGRAY);
            DrawText("Play Sequential", sequentialButton.x + 50, sequentialButton.y + 15, 20, WHITE);

            DrawRectangleRec(parallelButton, DARKGRAY);
            DrawText("Play Parallel", parallelButton.x + 50, parallelButton.y + 15, 20, WHITE);

            DrawRectangleRec(comparisonButton, DARKGRAY);
            DrawText("Comparison", comparisonButton.x + 50, comparisonButton.y + 15, 20, WHITE);

            EndDrawing();
        }

        if (gameMode == SEQUENTIAL || gameMode == PARALLEL) {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
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
            } else if (IsKeyPressed(KEY_D)) {
                simulation->createDeterminedState();
            } else if (IsKeyPressed(KEY_S)) {
                simulation->createDeterminedStateScaled();
            } else if (IsKeyPressed(KEY_C)) {
                simulation->clearGrid();
            }

            simulation->update();

            BeginDrawing();

            ClearBackground(BACKGROUND_COLOR);
            simulation->draw();

            int fps = GetFPS();
            DrawText(TextFormat("%2i FPS", fps), 10, 10, 30, WHITE);

            EndDrawing();
        }

        if (gameMode == COMPARISON) {
            // TODO
            BeginDrawing();
            ClearBackground(BACKGROUND_COLOR);
            DrawText("TODOOO", 400, 100, 30, BLACK);
            EndDrawing();
        }
    }

    CloseWindow();
    return 0;
}
