#include "benchmark.h"
#include "maze.h"
#include "graph.h"
#include <iostream>
#include <chrono>
#include <iomanip>
#include <vector>

void runBenchmark(const std::vector<std::pair<long, long>>& sizes) {
    std::cout << "\n" << std::string(90, '-') << "\n";
    std::cout << "BENCHMARK DE ALGORITMOS DE BUSCA - VARIANDO TAMANHO DO LABIRINTO\n";
    std::cout << std::string(90, '-') << "\n\n";
    
    std::vector<BenchmarkResult> results;
    
    // Executar benchmark para cada tamanho
    for (const auto& size : sizes) {
        long width = size.first;
        long height = size.second;
        
        std::cout << "Testando labirinto " << width << "x" << height << " (área: " << (width * height) << ")...\n";
        
        // Criar labirinto
        Maze maze(width, height);
        maze.createMaze();
        
        // Criar grafo
        Graph graph(maze.getMazeMap());
        
        // Benchmark A*
        auto startAStar = std::chrono::high_resolution_clock::now();
        Path exitPathAStar = graph.getExitPath(A_STAR_ALGORITHM);
        auto endAStar = std::chrono::high_resolution_clock::now();
        auto durationAStar = std::chrono::duration_cast<std::chrono::microseconds>(endAStar - startAStar);
        
        // Benchmark DFS
        auto startDFS = std::chrono::high_resolution_clock::now();
        Path exitPathDFS = graph.getExitPath(DFS_ALGORITHM);
        auto endDFS = std::chrono::high_resolution_clock::now();
        auto durationDFS = std::chrono::duration_cast<std::chrono::microseconds>(endDFS - startDFS);
        
        results.push_back({
            width,
            height,
            width * height,
            durationAStar.count(),
            durationDFS.count(),
            !exitPathAStar.empty(),
            !exitPathDFS.empty()
        });
        
        std::cout << "  ✓ Concluído\n\n";
    }
    
    // Exibir tabela comparativa
    std::cout << "\n" << std::string(130, '-') << "\n";
    std::cout << "RESULTADOS DO BENCHMARK\n";
    std::cout << std::string(130, '-') << "\n\n";
    
    // Cabeçalho
    std::cout << std::left 
              << std::setw(15) << "Tamanho"
              << std::setw(12) << "Área"
              << std::setw(20) << "A* (μs)"
              << std::setw(20) << "A* (ms)"
              << std::setw(20) << "DFS (μs)"
              << std::setw(20) << "DFS (ms)"
              << std::setw(15) << "Speedup"
              << std::setw(12) << "A* Found"
              << std::setw(12) << "DFS Found"
              << "\n";
    std::cout << std::string(130, '-') << "\n";
    
    // Linhas de dados
    for (const auto& result : results) {
        double speedup = (result.aStarTime > 0) ? static_cast<double>(result.dfsTime) / result.aStarTime : 0;
        
        std::cout << std::left 
                  << std::setw(15) << (std::to_string(result.width) + "x" + std::to_string(result.height))
                  << std::setw(12) << result.area
                  << std::setw(20) << result.aStarTime
                  << std::setw(20) << std::fixed << std::setprecision(4) << (result.aStarTime / 1000.0)
                  << std::setw(20) << result.dfsTime
                  << std::setw(20) << std::fixed << std::setprecision(4) << (result.dfsTime / 1000.0)
                  << std::setw(15) << std::fixed << std::setprecision(2) << speedup
                  << std::setw(12) << (result.aStarFound ? "✓ Sim" : "❌ Não")
                  << std::setw(12) << (result.dfsFound ? "✓ Sim" : "❌ Não")
                  << "\n";
    }
    
    std::cout << "\n" << std::string(130, '-') << "\n";
    
    // Análise
    std::cout << "\nANÁLISE DOS RESULTADOS:\n";
    std::cout << std::string(50, '-') << "\n";
    
    // Encontrar tempos mínimos e máximos para A* e DFS
    long minAStar = results[0].aStarTime;
    long maxAStar = results[0].aStarTime;
    long minDFS = results[0].dfsTime;
    long maxDFS = results[0].dfsTime;
    
    // Iterar pelos resultados para encontrar os tempos mínimos e máximos
    for (const auto& result : results) {
        if (result.aStarTime < minAStar) minAStar = result.aStarTime;
        if (result.aStarTime > maxAStar) maxAStar = result.aStarTime;
        if (result.dfsTime < minDFS) minDFS = result.dfsTime;
        if (result.dfsTime > maxDFS) maxDFS = result.dfsTime;
    }
    
    // Exibir análise de crescimento
    std::cout << "A* - Tempo mínimo: " << std::fixed << std::setprecision(4) << (minAStar / 1000.0) << " ms\n";
    std::cout << "A* - Tempo máximo: " << std::fixed << std::setprecision(4) << (maxAStar / 1000.0) << " ms\n";
    std::cout << "A* - Crescimento: " << std::fixed << std::setprecision(2) << (static_cast<double>(maxAStar) / minAStar) << "x\n\n";
    
    // Exibir análise de crescimento para DFS
    std::cout << "DFS - Tempo mínimo: " << std::fixed << std::setprecision(4) << (minDFS / 1000.0) << " ms\n";
    std::cout << "DFS - Tempo máximo: " << std::fixed << std::setprecision(4) << (maxDFS / 1000.0) << " ms\n";
    std::cout << "DFS - Crescimento: " << std::fixed << std::setprecision(2) << (static_cast<double>(maxDFS) / minDFS) << "x\n";
    
    std::cout << "\n" << std::string(130, '-') << "\n\n";
}
