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

#include <stdio.h>
#include "raylib.h"

int main(void) {

    // 800x450 is 16:9
    InitWindow(800, 450, "Raylib");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {

        BeginDrawing();
        ClearBackground(SKYBLUE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}