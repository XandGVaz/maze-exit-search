#pragma once

#include <stdint.h>
#include <algorithm>
#include <vector>
#include <cmath>

/**
 * @def PATH_COST_SCALE Constante que representa a escala do custo do caminho, utilizada para calcular o custo total (g + h) dos nós no algoritmo A*.
 */
#define PATH_COST_SCALE 10

/**
 * @typedef CellValue Enum que representa os valores das células do labirinto, onde PATH_CELL (0) representa um caminho, WALL_CELL (1) representa uma parede e EXIT_CELL (7) representa a saída do labirinto.
 */
typedef enum{
    PATH_CELL = 0,
    WALL_CELL = 1,
    EXIT_CELL = 7
}CellValue;

/**
 * @brief Definição de tipo byte como um alias para byte, que é um tipo de dado inteiro sem sinal de 8 bits, 
 * 		  utilizado para representar os valores das células do labirinto (0: caminho, 1: parede, 7: saída do labirinto).
 */
typedef uint8_t byte;

/**
 * @brief Definição de tipo mapPosition como um alias para std::pair<long,long>, que é um par de inteiros que 
 * 		  representa a posição de uma célula do labirinto, onde o primeiro elemento é a coordenada X e o segundo 
 * 		  elemento é a coordenada Y.
 */
typedef std::pair<long,long> MapPosition;

/**
 * @brief Definição de tipo path como um alias para std::vector<MapPosition>, que é um vetor de pares de inteiros que 
 * 		  representa o caminho da saída do labirinto, onde cada par é a posição de uma célula do caminho.
 */
typedef std::vector<MapPosition> Path;

/**
 * @brief Função que calcula a distância entre duas posições do labirinto, utilizando a fórmula da distância euclidiana, e retorna o valor da distância multiplicado pela constante PATH_COST_SCALE.
 * @param pos1 Primeira posição do labirinto
 * @param pos2 Segunda posição do labirinto
 * @return Distância entre as duas posições multiplicada pela constante PATH_COST_SCALE.
 */
long distance(MapPosition pos1, MapPosition pos2);

/**
 * @brief Classe que representa o mapa do labirinto, com métodos para verificar a validade de uma posição, verificar se uma posição é a saída do labirinto, definir a posição de início e saída do labirinto, preencher o mapa com um valor específico, acessar e modificar os valores das células do mapa e sobrecarga do operador por atribuição.
 *        O mapa do labirinto é representado por uma matriz de bytes, onde cada célula é representada por um número inteiro (0: caminho, 1: parede, 7: saída do labirinto).
 */
class Map{
    /**
     * @brief Matriz de bytes que representa o mapa do labirinto, onde cada célula é representada por um número inteiro (0: caminho, 1: parede, 7: saída do labirinto), o tamanho do mapa em X e Y, a posição de início e a posição de saída do labirinto.
     */
    std::vector<std::vector<byte>> _cells;

    /**
     * @brief Tamanho do mapa em X, tamanho do mapa em Y, posição de início e posição de saída do labirinto.
     */
    long _mapXLenght;
    /**
     * @brief Tamanho do mapa em Y, tamanho do mapa em X, posição de início e posição de saída do labirinto.
     */
    long _mapYLenght;

    /**
     * @brief Posição de início e posição de saída do labirinto, onde a posição de início é a posição da célula de início do labirinto e a posição de saída é a posição da célula de saída do labirinto.
     */
    MapPosition _start;
    /**
     * @brief Posição de saída e posição de início do labirinto, onde a posição de saída é a posição da célula de saída do labirinto e a posição de início é a posição da célula de início do labirinto.
     */
    MapPosition _exit;
public:
    /**
     * @brief Construtor da classe Map, que inicializa o tamanho do mapa em X e Y, a matriz de células do mapa preenchida com o valor de caminho (0) e a posição de início do mapa.
     * @param mapXLenght Tamanho do mapa em X
     * @param mapYLenght Tamanho do mapa em Y
     * @param start Posição de início do mapa
     */
    Map(long mapXLenght, long mapYLenght, MapPosition start): 
        _mapXLenght(mapXLenght), _mapYLenght(mapYLenght), _cells(mapYLenght, std::vector<byte>(mapXLenght, PATH_CELL)),
        _start(start){}

    /**
     * @brief Função que retorna o tamanho do mapa em X.
     * @return Tamanho do mapa em X.
     */
    long getMapXLenght() const { return _mapXLenght; }
    /**
     * @brief Função que retorna o tamanho do mapa em Y.
     * @return Tamanho do mapa em Y.
     */
    long getMapYLenght() const { return _mapYLenght; }

    /**
     * @brief Função que retorna a posição de início do mapa.
     * @return Posição de início do mapa.
     */
    MapPosition getStart() const { return _start; }
    /**
     * @brief Função que retorna a posição de saída do mapa.
     * @return Posição de saída do mapa.
     */
    MapPosition getExit() const { return _exit; }
    /**
     * @brief Função que verifica se uma posição é válida, ou seja, se a posição está dentro dos limites do mapa.
     * @param pos Posição a ser verificada
     * @return true se a posição é válida, false caso contrário.
     */
    bool positionIsValid(MapPosition pos);
    /**
     * @brief Função que verifica se uma posição é a saída do mapa, ou seja, se o valor da célula na posição é igual ao valor de saída (7).
     * @param pos Posição a ser verificada
     * @return true se a posição é a saída do mapa, false caso contrário.
     */
    bool positionIsExit(MapPosition pos);


    /**
     * @brief Função que define a posição de início do mapa, se a posição é válida.
     * @param pos Posição a ser definida como início
     * @return true se a posição foi definida como início, false caso contrário.
     */
    bool setStart(MapPosition pos);
    /**
     * @brief Função que define a posição de saída do mapa, se a posição é válida.
     * @param pos Posição a ser definida como saída
     * @return true se a posição foi definida como saída, false caso contrário.
     */
    bool setExit(MapPosition pos);


    /**
     * @brief Função que preenche o mapa com um valor específico, ou seja, define o valor de todas as células do mapa como o valor especificado.
     * @param value Valor a ser preenchido no mapa
     */
    void toFilledMap(CellValue value = WALL_CELL);

    /**
     * @brief Sobrecarga do operador de acesso, que permite acessar e modificar os valores das células do mapa utilizando a sintaxe map(pos) ou map(y,x), onde pos é um par de inteiros que representa a posição da célula e y e x são as coordenadas da célula.
     * @param pos Posição da célula a ser acessada ou modificada
     * @return Referência para o valor da célula na posição especificada.
     */
    byte& operator()(MapPosition pos);
    /**
     * @brief Sobrecarga do operador de acesso, que permite acessar e modificar os valores das células do mapa utilizando a sintaxe map(pos) ou map(y,x), onde pos é um par de inteiros que representa a posição da célula e y e x são as coordenadas da célula.
     * @param y Coordenada Y da célula a ser acessada ou modificada
     * @param x Coordenada X da célula a ser acessada ou modificada
     * @return Referência para o valor da célula na posição especificada.
     */
    byte& operator()(long y, long x);
    /**
     * @brief Sobrecarga do operador por atribuição, que copia o tamanho do mapa em X e Y, a matriz de células do mapa, a posição de início e a posição de saída de um objeto da classe Map para outro objeto da classe Map.
     * @param map2 Objeto da classe Map que será copiado para o objeto atual.
     * @return Referência para o objeto da classe Map que recebeu a cópia.
     */
    Map& operator=(const Map& map2);
};
