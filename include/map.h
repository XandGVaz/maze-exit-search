#pragma once
#include <stdint.h>
#include <algorithm>
#include <vector>

#define PATH_COST_SCALE 10

namespace Maping{
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


    typedef std::vector<MapPosition> Path;

    /**
     * @brief Definição de tipo map como um alias para byte**, que é uma matriz de segundo grau de bytes, utilizado 
     * 		  para representar o mapa do labirinto como uma matriz de bytes, onde cada célula é representada por um 
     * 		  número inteiro (0: caminho, 1: parede, 7: saída do labirinto).
     */
    typedef byte** Map;
    
    struct MapNode{
        MapPosition position;
        MapNode* previousNode;
        byte mapValue;
        long g;
        long h;
    };

    /**
     * @brief Função que retorna um mapa vazio, ou seja, somente com paredes nas bordas do labirinto e caminho no restante das células.
     * @param map_x_lenght Tamanho do labirinto em X
     * @param map_y_lenght Tamanho do labirinto em Y
     * @return String que representa o mapa do labirinto vazio.
     */
    Map getEmptyMap(long map_x_lenght, long map_y_lenght);
    
    /**
     * @brief Função que retorna um mapa preenchido, ou seja, somente com paredes em todas as células do labirinto.
     * @param map_x_lenght Tamanho do labirinto em X
     * @param map_y_lenght Tamanho do labirinto em Y
     * @return String que representa o mapa do labirinto preenchido.
     */
    Map getFilledMap(long map_x_lenght, long map_y_lenght);

    long distance(MapPosition pos1, MapPosition pos2);

    byte getMapValue(Map map, MapPosition position);

    byte setMapValue(Map map, MapPosition position, byte value);
};
