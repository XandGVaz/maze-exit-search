#include <iostream>
#include "maze.h"
#include "graph.h"

int main() {
    // Cria um labirinto aleatório
    Maze maze(40, 23);
    maze.createMaze();
    std::cout << "Labirinto gerado:\n";
    maze.ptintMaze();
    
    // Cria um grafo a partir do mapa do labirinto
    Graph graph(maze.getMazeMap());
    
    // Encontra o caminho de saída utilizando o algoritmo A*
    Path exitPath = graph.getExitPath(A_STAR_ALGORITHM);
    
    // Imprime o labirinto com o caminho de saída
    std::cout << "\nLabirinto com o caminho de saída (A*):\n";
    maze.ptintMaze(exitPath);
    
    return 0;
}