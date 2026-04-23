#include "benchmark.h"
#include "visualization.h"
#include <vector>

int main() {
    // Tamanhos de labirintos a testar
    std::vector<std::pair<long, long>> sizes = {
        {20, 20},   // Pequeno
        {40, 40},   // Médio-pequeno
        {60, 60},   // Médio
        {80, 80},   // Médio-grande
        {100, 100}  // Grande
    };
    
    // Demonstração com o primeiro tamanho
    demonstrateMaze(sizes[2].first, sizes[2].second);
    
    // Executar benchmark
    runBenchmark(sizes);
    
    return 0;
}