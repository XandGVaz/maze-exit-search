#pragma once

#include <vector>
#include <utility>

/**
 * @struct BenchmarkResult
 * @brief Estrutura para armazenar os resultados do benchmark dos algoritmos de busca A* e DFS, incluindo o tamanho do labirinto, o tempo gasto por cada algoritmo em microsegundos, e se cada algoritmo conseguiu encontrar a saída do labirinto.
 */
struct BenchmarkResult {
    long width;
    long height;
    long area;
    long aStarTime;  // em microsegundos
    long dfsTime;    // em microsegundos
    bool aStarFound;
    bool dfsFound;
};

/**
 * @brief Função que executa o benchmark dos algoritmos de busca A* e DFS para encontrar a saída de labirintos de diferentes tamanhos, medindo o tempo gasto por cada algoritmo e exibindo os resultados em uma tabela comparativa, 
 *        além de realizar uma análise dos resultados para identificar tendências de crescimento dos tempos de execução dos algoritmos à medida que o tamanho do labirinto aumenta.
 * @param sizes Vetor de pares de inteiros que representa os tamanhos dos labirintos a serem testados, onde cada par é formado por um inteiro que representa a largura do labirinto e um inteiro que representa a altura do labirinto.
 */
void runBenchmark(const std::vector<std::pair<long, long>>& sizes);
