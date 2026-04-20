#pragma once

#include <vector>
#include <utility>

struct BenchmarkResult {
    long width;
    long height;
    long area;
    long aStarTime;  // em microsegundos
    long dfsTime;    // em microsegundos
    bool aStarFound;
    bool dfsFound;
};

// Executa benchmark comparando A* e DFS em labirintos de diferentes tamanhos
void runBenchmark(const std::vector<std::pair<long, long>>& sizes);
