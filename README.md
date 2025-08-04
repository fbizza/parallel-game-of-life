# parallel-game-of-life
An interactive, parallelized implementation of Conway's Game of Life, developed in C++ using [Raylib](https://www.raylib.com/) for GUI and OpenMP for multithreading.

**Three execution modes**:
  - **Sequential**: baseline single thread simulation.
  - **Parallel**: parallel version using OpenMP, by default it uses all available cores of your machine.
  - **Comparison**: allows selection of thread count and shows speedup graph.

**Controls**:
| Key     | Action                                  |
| ------- | --------------------------------------- |
| `ENTER` | Start the simulation                    |
| `SPACE` | Pause the simulation                    |
| `R`     | Initialize the grid with a random state |
| `D`     | Load a fixed, determined pattern ("CIAO")|
| `S`     | Load a scaled version of the pattern    |
| `C`     | Clear the grid                          |

# Demo

**Sequential version**: it runs at ~26 FPS

https://github.com/user-attachments/assets/227d1251-18ed-4162-9e37-6baf89455ff0

**Parallel version**: it runs at ~62 FPS

https://github.com/user-attachments/assets/04c70d42-1b04-418d-a17e-2dedc5bce5c3

**Speedup graph**

https://github.com/user-attachments/assets/f58a9ff6-30a8-4a2e-97b0-d995d7651077

**Comparison with n threads**

https://github.com/user-attachments/assets/d24b1d17-a956-41fa-9a3d-5f4810f26273

# Customize the Grid Size

You can easily adjust the simulation's grid by modifying the constants in `main.cpp`. The relevant parameters are:

```cpp
const int WINDOW_WIDTH = 1200;
const int WINDOW_HEIGHT = 800;
const int CELL_SIZE = 5;


