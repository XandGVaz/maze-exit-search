#pragma once

#include <vector>
#include <utility>

/**
 * @brief Função que demonstra um labirinto imprimindo-o sem e com o caminho de saída.
 *        Cria um labirinto com o tamanho especificado, encontra o caminho de saída utilizando
 *        o algoritmo A* e exibe ambas as versões (sem e com o caminho).
 * @param width Largura do labirinto
 * @param height Altura do labirinto
 */
void demonstrateMaze(long width, long height);

/**
 * @brief Função que imprime um cabeçalho formatado para a seção de demonstração do labirinto.
 * @param width Largura do labirinto
 * @param height Altura do labirinto
 */
void printMazeDemoHeader(long width, long height);
