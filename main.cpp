#include "benchmark.h"

int main() {
    // Tamanhos de labirintos a testar
    std::vector<std::pair<long, long>> sizes = {
        {20, 15},   // Pequeno
        {30, 20},   // Médio-pequeno
        {40, 23},   // Médio
        {50, 30},   // Médio-grande
        {60, 35}    // Grande
    };
    
    // Executar benchmark
    runBenchmark(sizes);
    
    return 0;
}