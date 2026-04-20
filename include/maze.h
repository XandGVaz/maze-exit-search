#pragma once

#include <stdint.h>
#include <vector>
#include "map.h"

/**
 * @class Maze
 * @brief Classe que representa o labirinto, com métodos para gerar um labirinto aleatório, obter o mapa do labirinto e sobrecarga do operador por atribuição.
 *        O labirinto é representado por uma string de bytes, onde cada célula é representada por um número inteiro
 *        0: caminho, 1: parede, 7: saída do labirinto.
 */
class Maze{
	long _mazeX; 	   		// Tamanho do labirinto em X
	long _mazeY; 	   		// Tamanho do labirinto em Y
	Map  _mazeMap; 	   		// Mapa do labirinto representado por uma matriz de bytes, onde cada célula é representada por um número inteiro (0: caminho, 1: parede, 7: saída do labirinto)
	MapPosition _mazeExit; 	// Par de inteiros que representa a posição da saída do labirinto (índice da célula de saída)
	MapPosition _mazeStart; // Par de inteiros que representa a posição da célula de início do labirinto (índice da célula de início)
protected:
	/**
	 * @brief Função recursiva que cria os caminhos do labirinto a partir de uma célula de origem, utilizando busca em profundidade, e armazena as possíveis saídas do labirinto em um Matriz de pares de posições.
	 * @param x_origin Coordenada X da célula de origem
	 * @param y_origin Coordenada Y da célula de origem
	 * @param possibOuts Vetor de pares de posições que representa as possíveis saídas do labirinto, onde cada par é formado por uma posição de célula do meio e uma posição de célula vizinha que está fora do labirinto (saída do labirinto).
	 */
	void createPaths(long x_origin, long y_origin, std::vector<std::pair<MapPosition,MapPosition>> &possibOuts);
	
	/**
	 * @brief Função que gera um labirinto aleatório, preenchendo o mapa do labirinto com paredes e criando os caminhos do labirinto a partir de uma célula de início, utilizando busca em profundidade, e escolhendo uma saída aleatória entre as possíveis saídas do labirinto.
	 * @return Par de inteiros que representa a posição da célula de saída do labirinto (índice da célula de saída).
	 */
	MapPosition toRandomMaze();

public:
	/**
	 * @brief Construtor da classe Maze, que inicializa o tamanho do labirinto em X e Y, o mapa do labirinto como um mapa vazio e a posição da célula de início como o meio do labirinto.
	 * @param map_x_lenght Tamanho do labirinto em X
	 * @param map_y_lenght Tamanho do labirinto em Y
	 */
	Maze(long map_x_lenght, long map_y_lenght);

	/**
	 * @brief Destrutor da classe Maze, que libera a memória alocada para o mapa do labirinto.
	 */
	~Maze();

	/**
	 * @brief Função que gera um labirinto aleatório, preenchendo o mapa do labirinto com paredes e criando os caminhos do labirinto a partir de uma célula de início, utilizando busca em profundidade, e escolhendo uma saída aleatória entre as possíveis saídas do labirinto.
	 * @return Matriz de bytes que representa o mapa do labirinto gerado, onde cada célula é representada por um número inteiro (0: caminho, 1: parede, 7: saída do labirinto).
	 */
	Map createMaze();

	/**
	 * @brief Função que retorna o mapa do labirinto gerado, representado por uma matriz de bytes, onde cada célula é representada por um número inteiro (0: caminho, 1: parede, 7: saída do labirinto).
	 * @return Matriz de bytes que representa o mapa do labirinto gerado.
	 */
	Map getMazeMap(){ return _mazeMap; }

	/**
	 * @brief Função que retorna a posição da célula de saída do labirinto, representada por um par de inteiros (índice da célula de saída).
	 * @return Par de inteiros que representa a posição da célula de saída do labirinto (índice da célula de saída).
	 */
	MapPosition getExit(){ return _mazeExit; }

	/**
	 * @brief Sobrecarga do operador por atribuição, que copia o tamanho do labirinto em X e Y, o mapa do labirinto e a posição da célula de saída de um objeto da classe Maze para outro objeto da classe Maze.
	 * @param maze2 Objeto da classe Maze que será copiado para o objeto atual.
	 * @return Referência para o objeto da classe Maze que recebeu a cópia.
	 */
	Maze& operator =(const Maze& maze2);
	
	/**
	 * @brief Função que imprime o mapa do labirinto gerado, onde cada célula é representada por um caractere (█: parede, espaço: caminho, E: saída do labirinto).
	 */
	void ptintMaze();
};