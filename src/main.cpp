// #include <iostream>
// #include <omp.h>
//
// int main() {
// #pragma omp parallel
//     {
//         std::cout << "thread " << omp_get_thread_num() << std::endl;
//     }
//     return 0;
// }

#include <raylib.h>
#include <iostream>
#include "logic/SequentialSimulation.h"
#include "logic/ParallelSimulation.h"
int main()
{
    SetTraceLogLevel(LOG_ERROR);
    Color BACKGROUND_COLOR = {100, 100, 100, 255};
    const int WINDOW_WIDTH = 1200;
    const int WINDOW_HEIGHT = 800;
    const int CELL_SIZE = 25;
    int FPS = 60;

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Titolo");
    SetTargetFPS(FPS);

    Simulation* simulation = new SequentialSimulation(WINDOW_WIDTH, WINDOW_HEIGHT, CELL_SIZE);
    // Simulation* simulation = new ParallelSimulation(WINDOW_WIDTH, WINDOW_HEIGHT, CELL_SIZE);

    while(WindowShouldClose() == false)
    {
        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            Vector2 mousePosition = GetMousePosition();
            int row = mousePosition.y / CELL_SIZE;
            int column = mousePosition.x / CELL_SIZE;
            simulation->toggleCell(row, column);
        }

        if(IsKeyPressed(KEY_ENTER))
        {
            simulation->start();
            SetWindowTitle("Quando parte");
        }
        else if(IsKeyPressed(KEY_SPACE))
        {
            simulation->stop();
            SetWindowTitle("Quando lo stoppo");
        }
        else if(IsKeyPressed(KEY_R))
        {
            simulation->createRandomState();
        }
        else if(IsKeyPressed(KEY_C))
        {
            simulation->clearGrid();
        }

        simulation->update();

        BeginDrawing();
        ClearBackground(BACKGROUND_COLOR); // to have a grid effect
        simulation->draw();
        EndDrawing();
    }

    delete simulation;

    CloseWindow();
}