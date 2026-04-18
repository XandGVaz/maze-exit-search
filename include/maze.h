#pragma once

#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <random>

/**
 * @brief Função que retorna um mapa vazio, ou seja, somente com paredes nas bordas do labirinto e caminho no restante das células.
 * @param map_x Tamanho do labirinto em X
 * @param map_y Tamanho do labirinto em Y
 * @return String que representa o mapa do labirinto vazio.
 */
char *getEmptyMap(int map_x, int map_y);

/**
 * @brief Função que retorna um mapa preenchido, ou seja, somente com paredes em todas as células do labirinto.
 * @param map_x Tamanho do labirinto em X
 * @param map_y Tamanho do labirinto em Y
 * @return String que representa o mapa do labirinto preenchido.
 */
char *getFilledMap(int map_x, int map_y);

/**
 * @class Maze
 * @brief Classe que representa o labirinto, com métodos para gerar um labirinto aleatório, obter o mapa do labirinto e sobrecarga do operador por atribuição.
 *        O labirinto é representado por uma string de caracteres, onde cada célula é representada por um número inteiro
 *        0: caminho, 1: parede, 7: saída do labirinto.
 */
class Maze{
	int _mazeX; // Tamanho do labirinto em X
	int _mazeY; // Tamanho do labirinto em Y

	char *_maze; // String que representa o mapa do labirinto

protected:
	/**
	 * @brief Método que implementa a geracão dos caminhos internos do labirinto, utilizando busca em profundidade.
	 *        O método recebe as coordenadas da célula de origem e um vetor de pares de inteiros que representa as possíveis saídas do labirinto, que é atualizado durante a execução do método.
	 * @param x_origin Coordenada X da célula de origem
	 * @param y_origin Coordenada Y da célula de origem
	 * @param possibOuts Vetor de pares de inteiros que representa as possíveis saídas do labirinto, que é atualizado durante a execução do método	
	 */
	void createPaths(int x_origin, int y_origin, std::vector<std::pair<int,int>> &possibOuts);
	
	/**
	 * @brief Método que gera um labirinto aleatório, utilizando o método createPaths para gerar os caminhos internos do labirinto e escolhendo uma saída aleatória entre as possíveis saídas geradas durante a execução do método createPaths.
	 *        O método retorna o índice da célula de saída do labirinto.
	 * @return Índice da célula de saída do labirinto
	 */
	int toRandomMaze();
	
	/**
	 * @brief Método que retorna o mapa do labirinto em string padrão, onde cada célula é representada por um número inteiro.
	 * @return String que representa o mapa do labirinto
	 */
	char* getMazeMap();

public:
    /**
	 * @brief Construtor da classe, que recebe o tamanho do labirinto em X e Y e inicializa o mapa do labirinto como um mapa vazio.
	 * @param map_x Tamanho do labirinto em X
	 * @param map_y Tamanho do labirinto em Y
	 */
	Maze(int map_x, int map_y);

	/**
	 * @brief Destrutor da classe, que libera a memória alocada para o mapa do labirinto.
	 */
	~Maze();

	/**
	 * @brief Método que gera um labirinto aleatório e retorna o mapa do labirinto em string padrão, onde cada célula é representada por um número inteiro.
	 * @return String que representa o mapa do labirinto
	 */
	char* createMaze();
	
	/**
	 * @brief Sobrecarga do operador por atribuição, que copia o tamanho do labirinto em X e Y e o mapa do labirinto de um objeto para outro.
	 * @param maze2 Objeto da classe Maze que será copiado
	 * @return Referência para o objeto da classe Maze que recebeu a cópia
	 */
	Maze& operator =(const Maze& maze2);
};