#include "benchmark.h"
#include "visualization.h"
#include <vector>

int main() {
    // Tamanhos de labirintos a testar
    std::vector<std::pair<long, long>> sizes = {
        {20, 15},   // Pequeno
        {30, 20},   // Médio-pequeno
        {40, 23},   // Médio
        {50, 30},   // Médio-grande
        {60, 35}    // Grande
    };
    
    // Demonstração com o primeiro tamanho
    demonstrateMaze(sizes[0].first, sizes[0].second);
    
    // Executar benchmark
    runBenchmark(sizes);
    
    return 0;
}