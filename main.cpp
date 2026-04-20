#include <iostream>
#include "maze.h"

using namespace Maping;

int main() {
    Maze maze(150, 39);
    maze.createMaze();
    std::cout << "Labirinto gerado:\n";
    maze.ptintMaze();
    return 0;
}