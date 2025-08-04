#include <raylib.h>
#include <memory>
#include "logic/SequentialSimulation.h"
#include "logic/ParallelSimulation.h"
#include "logic/ComparisonSimulation.h"
#include <omp.h>

enum GameMode {
    MENU,
    SEQUENTIAL,
    PARALLEL,
    COMPARISON,
    THREAD_SELECTION
};

int main() {
    SetTraceLogLevel(LOG_ERROR);
    Color BACKGROUND_COLOR = {100, 100, 100, 255};
    const int WINDOW_WIDTH = 1200;
    const int WINDOW_HEIGHT = 800;
    const int CELL_SIZE = 5;
    const int FPS = 90;

    int maxThreads = omp_get_max_threads();
    int numThreads = maxThreads; // used as default in the parallel simulation TODO: check if max is also optimal

    bool comparisonRun = false;
    std::unique_ptr<ComparisonSimulation> comparisonSim = nullptr;

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
                SetMouseCursor(MOUSE_CURSOR_DEFAULT);
                if (CheckCollisionPointRec(mousePosition, sequentialButton)) {
                    gameMode = SEQUENTIAL;
                    simulation = std::make_unique<SequentialSimulation>(WINDOW_WIDTH, WINDOW_HEIGHT, CELL_SIZE);
                } else if (CheckCollisionPointRec(mousePosition, parallelButton)) {
                    gameMode = PARALLEL;
                    simulation = std::make_unique<ParallelSimulation>(WINDOW_WIDTH, WINDOW_HEIGHT, CELL_SIZE, numThreads);
                } else if (CheckCollisionPointRec(mousePosition, comparisonButton)) {
                    gameMode = THREAD_SELECTION;
                }
            }

            BeginDrawing();

            ClearBackground(BACKGROUND_COLOR);

            DrawText("Choose a Simulation Mode", 410, 150, 30, BLACK);

            DrawRectangleRec(sequentialButton, DARKGRAY);
            DrawText("Play Sequential", sequentialButton.x + 27, sequentialButton.y + 15, 20, WHITE);

            DrawRectangleRec(parallelButton, DARKGRAY);
            DrawText("Play Parallel", parallelButton.x + 40, parallelButton.y + 15, 20, WHITE);

            DrawRectangleRec(comparisonButton, DARKGRAY);
            DrawText("Comparison", comparisonButton.x + 47, comparisonButton.y + 15, 20, WHITE);

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

        if (gameMode == THREAD_SELECTION) {
            if (IsKeyPressed(KEY_UP) && numThreads < maxThreads) {
                numThreads++;
            } else if (IsKeyPressed(KEY_DOWN) && numThreads > 1) {
                numThreads--;
            } else if (IsKeyPressed(KEY_ENTER)) {
                gameMode = COMPARISON;
            }

            BeginDrawing();
            ClearBackground(BACKGROUND_COLOR);

            DrawText("Select number of threads", 290, 200, 50, WHITE);
            DrawText(TextFormat("Threads: "), 420, 360, 70, BLACK);

            // different color for the number
            int textWidth = MeasureText("Threads: ", 70);
            DrawText(TextFormat("%d", numThreads), 420 + textWidth, 360, 70, DARKGREEN);

            DrawText("Press UP/DOWN to change, ENTER to confirm", 370, 600, 20, BLACK);
            DrawText(TextFormat("(Number of threads available on this machine: %d)", maxThreads), 360, 635, 20, BLACK);


            EndDrawing();
        }

        if (gameMode == COMPARISON && !comparisonRun) {
            comparisonSim = std::make_unique<ComparisonSimulation>(WINDOW_WIDTH, WINDOW_HEIGHT, CELL_SIZE, numThreads);
            //todo: pass number of threads
            comparisonSim->runComparison();
            comparisonRun = true; // to only run it once
        }

        if (gameMode == COMPARISON) {
            if (comparisonRun) {
                BeginDrawing();
                ClearBackground(BACKGROUND_COLOR);

                const char* title = "Comparison Results";
                int titleFontSize = 60;
                int titleWidth = MeasureText(title, titleFontSize);
                DrawText(title, (WINDOW_WIDTH - titleWidth) / 2, 190, titleFontSize, BLACK);

                int textFontSize = 28;
                int spacing = 50;
                int startY = 290;
                int labelX = WINDOW_WIDTH / 2 - 200;

                DrawText(TextFormat("Sequential Time:"), labelX, startY, textFontSize, BLACK);
                DrawText(TextFormat("%.4f s", comparisonSim->getSequentialTime()), labelX + 300, startY, textFontSize, WHITE);

                DrawText("Parallel Time:", labelX, startY + spacing, textFontSize, BLACK);
                DrawText(TextFormat("%.4f s", comparisonSim->getParallelTime()), labelX + 300, startY + spacing, textFontSize, WHITE);

                DrawText("Speedup:", labelX, startY + spacing * 2, textFontSize, BLACK);
                DrawText(TextFormat("%.2fx", comparisonSim->getSpeedup()), labelX + 300, startY + spacing * 2, textFontSize,
                         comparisonSim->getSpeedup() < 1.0 ? RED : GREEN);

                const char* hint = "Press ESC to exit";
                int hintFontSize = 20;
                int hintWidth = MeasureText(hint, hintFontSize);
                DrawText(hint, (WINDOW_WIDTH - hintWidth) / 2, startY + spacing * 4, hintFontSize, GRAY);

                EndDrawing();
            }

        }
    }

    CloseWindow();
    return 0;
}
