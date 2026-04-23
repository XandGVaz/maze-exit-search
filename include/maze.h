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
	/**
	 * @brief Mapa do labirinto, representado por uma matriz de bytes, onde cada célula é representada por um número inteiro (0: caminho, 1: parede, 7: saída do labirinto).
	 */
	Map  _mazeMap; 	   	
protected:
	/**
	 * @brief Função recursiva que cria os caminhos do labirinto a partir de uma célula de início, utilizando busca em profundidade, e armazenando as possíveis saídas do labirinto em um vetor de pares de posições, onde cada par de posições representa a posição da célula de saída do labirinto e a posição da célula de início do labirinto.
	 * @param yOrigin Coordenada Y da célula de início do labirinto.
	 * @param xOrigin Coordenada X da célula de início do labirinto.
	 * @param possibOuts Vetor de pares de posições para armazenar as possíveis saídas do labirinto, onde cada par de posições representa a posição da célula de saída do labirinto e a posição da célula de início do labirinto.
	 * @return Vetor de pares de posições que representa as possíveis saídas do labirinto, onde cada par de posições representa a posição da célula de saída do labirinto e a posição da célula de início do labirinto.
	 */
	std::vector<std::pair<MapPosition,MapPosition>> createPaths(long yOrigin, long xOrigin);
	
	/**
	 * @brief Função que gera um labirinto aleatório, preenchendo o mapa do labirinto com paredes e criando os caminhos do labirinto a partir de uma célula de início, utilizando busca em profundidade, e escolhendo uma saída aleatória entre as possíveis saídas do labirinto.
	 * @return Par de inteiros que representa a posição da célula de saída do labirinto (índice da célula de saída).
	 */
	MapPosition toRandomMaze();

public:
	/**
	 * @brief Construtor da classe Maze, que inicializa o tamanho do labirinto em X e Y, o mapa do labirinto como um mapa vazio e a posição da célula de início como o meio do labirinto.
	 * @param mapXLenght Tamanho do labirinto em X
	 * @param mapYLenght Tamanho do labirinto em Y
	 */
	Maze(long mapXLenght, long mapYLenght): 
		_mazeMap(mapXLenght, mapYLenght, {mapYLenght/2, mapXLenght/2}){}

	/**
	 * @brief Função que gera um labirinto aleatório, preenchendo o mapa do labirinto com paredes e criando os caminhos do labirinto a partir de uma célula de início, utilizando busca em profundidade, e escolhendo uma saída aleatória entre as possíveis saídas do labirinto.
	 * @return Matriz de bytes que representa o mapa do labirinto gerado, onde cada célula é representada por um número inteiro (0: caminho, 1: parede, 7: saída do labirinto).
	 */
	Map& createMaze();

	/**
	 * @brief Função que retorna o mapa do labirinto gerado, representado por uma matriz de bytes, onde cada célula é representada por um número inteiro (0: caminho, 1: parede, 7: saída do labirinto).
	 * @return Matriz de bytes que representa o mapa do labirinto gerado.
	 */
	Map& getMazeMap(){ return _mazeMap; }

	/**
	 * @brief Função que retorna o tamanho do labirinto em X.
	 * @return Tamanho do labirinto em X.
	 */
	long getMazeXLenght() const { return _mazeMap.getMapXLenght(); }

	/**
	 * @brief Função que retorna o tamanho do labirinto em Y.
	 * @return Tamanho do labirinto em Y.
	 */
	long getMazeYLenght() const { return _mazeMap.getMapYLenght(); }

	/**
	 * @brief Função que retorna a posição da célula de início do labirinto, representada por um par de inteiros (índice da célula de início).
	 * @return Par de inteiros que representa a posição da célula de início do labirinto (índice da célula de início).
	 */
	MapPosition getStart() const { return _mazeMap.getStart(); }

	/**
	 * @brief Função que retorna a posição da célula de saída do labirinto, representada por um par de inteiros (índice da célula de saída).
	 * @return Par de inteiros que representa a posição da célula de saída do labirinto (índice da célula de saída).
	 */
	MapPosition getExit() const { return _mazeMap.getExit(); }

	/**
	 * @brief Sobrecarga do operador por atribuição, que copia o tamanho do labirinto em X e Y, o mapa do labirinto e a posição da célula de saída de um objeto da classe Maze para outro objeto da classe Maze.
	 * @param maze2 Objeto da classe Maze que será copiado para o objeto atual.
	 * @return Referência para o objeto da classe Maze que recebeu a cópia.
	 */
	Maze& operator =(const Maze& maze2);
	
	/**
	 * @brief Função que imprime o labirinto no console, utilizando caracteres para representar as paredes, os caminhos, a célula de início e a célula de saída do labirinto. Se um caminho de saída for fornecido, ele também será impresso no console.
	 * @param exitPath Vetor de posições representando o caminho de saída. Se o vetor estiver vazio, o caminho de saída não será impresso.
	 */
	void ptintMaze(Path exitPath = {});
};