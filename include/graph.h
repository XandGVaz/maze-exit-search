#pragma once

#include "map.h"
#include <vector>
#include <expected>
#include <set>

/**
 * @typedef SearchAlgorithm Enum que representa os algoritmos de busca disponíveis para encontrar o caminho de saída do labirinto, onde A_STAR_ALGORITHM (0) representa o algoritmo A* e DFS_ALGORITHM (1) representa o algoritmo de busca em profundidade (DFS).
 */
typedef enum{
    A_STAR_ALGORITHM = 0U,
    DFS_ALGORITHM = 1
}SearchAlgorithm;

/**
 * @class Node
 * @brief Classe que representa um nó do grafo, com atributos para a posição do nó, os nós vizinhos, o nó prévio, o valor da célula correspondente no mapa, os custos g e h para o algoritmo A* e sobrecarga dos operadores de comparação e atribuição.
 *        O nó é utilizado para representar as células do mapa que não são paredes, e as conexões entre os nós são estabelecidas com base nas posições adjacentes no mapa.
 */
class Node{
    /**
     * @brief Atributos do nó, incluindo a posição do nó, os nós vizinhos, o nó prévio, o valor da célula correspondente no mapa, os custos g e h para o algoritmo A*.
     */
    MapPosition _position;
    /**
     * @brief Nós vizinhos, representados por um vetor de posições dos nós vizinhos, onde cada posição é a posição de uma célula adjacente no mapa que não é uma parede.
     */
    std::vector<MapPosition> _neighborsPositions;
    /**
     * @brief Nó prévio, representado por uma posição do nó prévio, que é a posição de uma célula adjacente no mapa que é o nó anterior no caminho encontrado para a saída do labirinto.
     */
    MapPosition _previousPosition;
    /**
     * @brief Valor da célula correspondente no mapa, representado por um byte, onde o valor é o número inteiro que representa a célula no mapa (0: caminho, 1: parede, 7: saída do labirinto).
     */
    byte _val;
    /**
     * @brief Custos g e h para o algoritmo A*, onde g é o custo do caminho desde o nó inicial até o nó atual, e h é a heurística que estima o custo do caminho do nó atual até a saída do labirinto.
     */
    long _h;
    /**
     * @brief Custo g do caminho desde o nó inicial até o nó atual, utilizado para o algoritmo A*.
     */
    long _g;
public:
    /**
     * @brief Construtor da classe Node, que inicializa a posição do nó, o valor da célula correspondente no mapa, os custos g e h para o algoritmo A* e o nó prévio.
     * @param pos Posição do nó, representada por um par de inteiros que representa a posição de uma célula do labirinto (coordenada X e coordenada Y).
     * @param value Valor da célula correspondente no mapa, representado por um byte, onde o valor é o número inteiro que representa a célula no mapa (0: caminho, 1: parede, 7: saída do labirinto).
     */
    Node(MapPosition pos, byte value);

    /**
     * @brief Método que adiciona um nó vizinho à lista de nós vizinhos do nó atual, onde o nó vizinho é representado por um ponteiro para um objeto da classe Node.
     * @param neighbor Ponteiro para o nó vizinho a ser adicionado à lista de nós vizinhos do nó atual.
     */
    void addNeighbor(Node* neighbor);

    /**
     * @brief Método que define o nó prévio do nó atual, onde o nó prévio é representado por um ponteiro para um objeto da classe Node.
     * @param previous Ponteiro para o nó prévio a ser definido para o nó atual.
     */
    void setPrevious(Node* previous);
    /**
     * @brief Método que define o custo h do nó atual, utilizado para o algoritmo A*.
     * @param h Custo h a ser definido para o nó atual, que é a heurística que estima o custo do caminho do nó atual até a saída do labirinto.
     */
    void setH(long h);
    /**
     * @brief Método que define o custo g do nó atual, utilizado para o algoritmo A*.
     * @param g Custo g a ser definido para o nó atual, que é o custo do caminho desde o nó inicial até o nó atual.
     */
    void setG(long g);

    /**
     * @brief Método que retorna a posição do nó, os nós vizinhos, o nó prévio, o valor da célula correspondente no mapa, os custos g e h para o algoritmo A* e o custo total f (g + h) do nó atual.
     * @return Posição do nó, nós vizinhos, nó prévio, valor da célula correspondente no mapa, custos g e h para o algoritmo A* e custo total f do nó atual.
     */
    MapPosition getPos() const { return _position; }
    /**
     * @brief Método que retorna os nós vizinhos do nó atual, representados por um vetor de posições dos nós vizinhos, onde cada posição é a posição de uma célula adjacente no mapa que não é uma parede.
     * @return Nós vizinhos do nó atual, representados por um vetor de posições dos nós vizinhos.
     */
    std::vector<MapPosition>& getNeighbors(){ return _neighborsPositions; }
    /**
     * @brief Método que retorna o nó prévio do nó atual, representado por uma posição do nó prévio, que é a posição de uma célula adjacente no mapa que é o nó anterior no caminho encontrado para a saída do labirinto.
     * @return Nó prévio do nó atual, representado por uma posição do nó prévio.
     */
    MapPosition getPrevious() const { return _previousPosition; }

    /**
     * @brief Método que retorna função h(n), denominada heurística.
     */
    long getH() const { return _h; }
    /**
     * @brief Método que retorna função g(n), que é o custo do caminho desde o nó inicial até o nó atual.
     */
    long getG() const { return _g; }
    /**
     * @brief Método que retorna função f(n), que é o custo total do nó atual, calculado como f(n) = g(n) + h(n).
     */
    long getF() const { return _g + _h; }

    // Sobrecarga dos operadores de comparação e atribuição para a classe Node, onde os operadores de comparação são baseados no custo total f do nó atual, e o operador de atribuição copia os atributos do nó1 para o nó atual.
    friend bool operator <(const Node& node1, const Node& node2);
    friend bool operator >(const Node& node1, const Node& node2);
    friend bool operator <=(const Node& node1, const Node& node2);
    friend bool operator >=(const Node& node1, const Node& node2);
    friend bool operator ==(const Node& node1, const Node& node2);
    friend bool operator !=(const Node& node1, const Node& node2);
    Node& operator =(const Node& node1);
};

/**
 * @struct CompareNodePointers
 * @brief Estrutura de comparação para ponteiros de nós, utilizada para ordenar os nós na lista de nós abertos do algoritmo A*, onde os nós são ordenados com base no custo total f do nó, e os ponteiros nulos são ordenados por endereço de memória.
 */
struct CompareNodePointers {
    bool operator()(Node* node1, Node* node2) const {
        if (node1 == nullptr || node2 == nullptr) {
            return node1 < node2; // Ordenação por endereço de memória para ponteiros nulos
        }
        return (*node1) <= (*node2);
    }
};

/**
 * @class Graph
 * @brief Classe que representa o grafo do labirinto, com métodos para criar o grafo a partir do mapa do labirinto, obter os nós do grafo, encontrar um nó específico do grafo com base em uma posição, encontrar o caminho de saída utilizando 
 *        os algoritmos de busca A* e DFS, e sobrecarga do operador por atribuição. O grafo é criado a partir do mapa do labirinto, onde cada célula do mapa que não é uma parede é representada por um nó no grafo, e as conexões entre os nós 
 *        são estabelecidas com base nas posições adjacentes no mapa. Os algoritmos de busca A* e DFS são implementados para encontrar o caminho de saída do labirinto, e o caminho de saída é reconstruído a partir dos nós encontrados pelos algoritmos de busca.
 */
class Graph{
    /**
     * @brief mapa do labirinto, representado por um objeto da classe Map, que é utilizado para criar o grafo e encontrar os nós correspondentes às posições do mapa.
     *        vetor de nós do grafo, onde cada nó representa uma célula do mapa que não é uma parede, e as conexões entre os nós são estabelecidas com base nas posições
     *        adjacentes no mapa. O vetor de nós é utilizado para armazenar os nós do grafo
     */
    Map _map;
    /**
     * @brief Vetor de nós do grafo, onde cada nó representa uma célula do mapa que não é uma parede, e as conexões entre os nós são estabelecidas com base nas posições adjacentes no mapa. O vetor de nós é utilizado para armazenar os nós do grafo.
     */
    std::vector<Node> _nodes;
protected:
    /**
     * @brief Função recursiva que implementa o algoritmo de busca A* para encontrar o caminho da célula de início até a célula de saída do labirinto, utilizando as listas de nós abertos e fechados para controlar os nós a serem visitados e os nós já visitados, e atualizando os custos g e h dos nós vizinhos.
     * @param currentNode Nó atual a ser visitado, representado por um ponteiro para um objeto da classe Node.
     * @param exit Posição da célula de saída do labirinto, representada por um par de inteiros que representa a posição de uma célula do labirinto (coordenada X e coordenada Y).
     * @param openNodes Lista de nós abertos para o algoritmo A*, representada por um conjunto de ponteiros para objetos da classe Node, onde os nós são ordenados com base no custo total f do nó.
     * @param visitedNodes Lista de nós fechados para o algoritmo A*, representada por um vetor de ponteiros para objetos da classe Node, onde os nós são os nós já visitados pelo algoritmo A*.
     */
    void aStarRecursive(Node* currentNode, MapPosition exit, std::set<Node*, CompareNodePointers>& openNodes, std::vector<Node*>& closedNodes);
    /**
     * @brief Função recursiva que implementa o algoritmo de busca em profundidade (DFS) para encontrar o caminho da célula de início até a célula de saída do labirinto, utilizando uma lista de nós visitados para controlar os nós já visitados, e visitando os nós vizinhos de forma recursiva.
     * @param currentNode Nó atual a ser visitado, representado por um ponteiro para um objeto da classe Node.
     * @param exit Posição da célula de saída do labirinto, representada por um par de inteiros que representa a posição de uma célula do labirinto (coordenada X e coordenada Y).
     * @param visitedNodes Lista de nós visitados para o algoritmo de busca em profundidade (DFS), representada por um vetor de ponteiros para objetos da classe Node, onde os nós são os nós já visitados pelo algoritmo DFS.
     */
    void dfsRecursive(Node* currentNode, MapPosition exit, std::vector<Node*>& visitedNodes);
public:
    /**
     * @brief Construtor da classe Graph, que inicializa o grafo a partir do mapa do labirinto, criando os nós correspondentes às células do mapa que não são paredes, e estabelecendo as conexões entre os nós com base nas posições adjacentes no mapa.
     * @param map Mapa do labirinto, representado por um objeto da classe Map, que é utilizado para criar o grafo e encontrar os nós correspondentes às posições do mapa.
     */
    Graph(const Map& map);

    /**
     * @brief Método que retorna os nós do grafo, representados por um vetor de objetos da classe Node, onde cada nó representa uma célula do mapa que não é uma parede, e as conexões entre os nós são estabelecidas com base nas posições adjacentes no mapa.
     * @return Nós do grafo, representados por um vetor de objetos da classe Node.
     */
    std::vector<Node>& getNodes(){ return _nodes; }
    /**
     * @brief Método que encontra um nó específico do grafo com base em uma posição, onde a posição é representada por um par de inteiros que representa a posição de uma célula do labirinto (coordenada X e coordenada Y), e retorna um ponteiro para o nó correspondente à posição, ou um ponteiro nulo se a posição não corresponder a nenhum nó do grafo.
     * @param pos Posição da célula do labirinto, representada por um par de inteiros que representa a posição de uma célula do labirinto (coordenada X e coordenada Y).
     * @return Ponteiro para o nó correspondente à posição, ou ponteiro nulo se a posição não corresponder a nenhum nó do grafo.
     */
    Node* getNode(MapPosition pos);

    /**
     * @brief Método que encontra o caminho de saída do labirinto utilizando o algoritmo de busca A*, onde o caminho de saída é representado por um vetor de posições das células do caminho, onde cada posição é representada por um par de inteiros que representa a posição de uma célula do labirinto (coordenada X e coordenada Y).
     * @param start Posição da célula de início do labirinto, representada por um par de inteiros que representa a posição de uma célula do labirinto (coordenada X e coordenada Y).
     * @param exit Posição da célula de saída do labirinto, representada por um par de inteiros que representa a posição de uma célula do labirinto (coordenada X e coordenada Y).
     * @return Caminho de saída do labirinto, representado por um vetor de posições das células do caminho, onde cada posição é representada por um par de inteiros que representa a posição de uma célula do labirinto (coordenada X e coordenada Y).
     */
    Path aStarSearch(MapPosition start, MapPosition exit);

    /**
     * @brief Método que encontra o caminho de saída do labirinto utilizando o algoritmo de busca em profundidade (DFS), onde o caminho de saída é representado por um vetor de posições das células do caminho, onde cada posição é representada por um par de inteiros que representa a posição de uma célula do labirinto (coordenada X e coordenada Y).
     * @param start Posição da célula de início do labirinto, representada por um par de inteiros que representa a posição de uma célula do labirinto (coordenada X e coordenada Y).
     * @param exit Posição da célula de saída do labirinto, representada por um par de inteiros que representa a posição de uma célula do labirinto (coordenada X e coordenada Y).
     * @return Caminho de saída do labirinto, representado por um vetor de posições das células do caminho, onde cada posição é representada por um par de inteiros que representa a posição de uma célula do labirinto (coordenada X e coordenada Y).
     */
    Path dfsSearch(MapPosition start, MapPosition exit);

    /**
     * @brief Método que encontra o caminho de saída do labirinto utilizando os algoritmos de busca A* e DFS, onde o algoritmo a ser utilizado é especificado por um parâmetro do tipo SearchAlgorithm, e retorna o caminho de saída como um vetor de posições das células do caminho, onde cada posição é representada por um par de inteiros que representa a posição de uma célula do labirinto (coordenada X e coordenada Y).
     * @param algorithm Algoritmo de busca a ser utilizado para encontrar o caminho de saída do labirinto, representado por um valor do tipo SearchAlgorithm (A_STAR_ALGORITHM ou DFS_ALGORITHM).
     * @return Caminho de saída do labirinto, representado por um vetor de posições das células do caminho, onde cada posição é representada por um par de inteiros que representa a posição de uma célula do labirinto (coordenada X e coordenada Y).
     */
    Path getExitPath(SearchAlgorithm algorithm);
};