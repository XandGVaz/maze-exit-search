#include "visualization.h"
#include "maze.h"
#include "graph.h"
#include <iostream>
#include <string>

void printMazeDemoHeader(long width, long height) {
    std::cout << "\n" << std::string(60, '=') << "\n";
    std::cout << "DEMONSTRAÇÃO: LABIRINTO " << width << "x" << height << "\n";
    std::cout << std::string(60, '=') << "\n\n";
}

void demonstrateMaze(long width, long height) {
    // Imprimir cabeçalho
    printMazeDemoHeader(width, height);
    
    // Criar labirinto
    Maze demoMaze(width, height);
    demoMaze.createMaze();
    
    // Imprimir labirinto sem o caminho
    std::cout << "LABIRINTO SEM CAMINHO:\n";
    std::cout << std::string(30, '-') << "\n";
    demoMaze.ptintMaze();
    
    std::cout << "\n";
    
    // Criar grafo e encontrar caminho
    Graph graph(demoMaze.getMazeMap());
    Path exitPath = graph.getExitPath(A_STAR_ALGORITHM);
    
    // Imprimir labirinto com o caminho
    std::cout << "LABIRINTO COM CAMINHO DE SAÍDA:\n";
    std::cout << std::string(30, '-') << "\n";
    demoMaze.ptintMaze(exitPath);
    
    std::cout << "\n\n";
}
