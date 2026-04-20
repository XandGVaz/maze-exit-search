#include "graph.h"
#include <algorithm>
#include <iostream>

/*======================================================= Implementação classe de Nodo =========================================================*/

Node::Node(MapPosition pos, byte value)
    : _position(pos), _val(value), _h(0), _g(0), _previousPosition({-1, -1}) {}

void Node::addNeighbor(Node* neighbor) {
    if (neighbor != nullptr) {
        _neighborsPositions.push_back(neighbor->getPos());
    }
}

void Node::setPrevious(Node* previous) {
    if (previous != nullptr) {
        _previousPosition = previous->getPos();
    }
}

void Node::setH(long h) {
    _h = h;
}

void Node::setG(long g) {
    _g = g;
}

// Operator overloads for Node
bool operator <(const Node& node1, const Node& node2) {
    return node1.getF() < node2.getF();
}

bool operator >(const Node& node1, const Node& node2) {
    return node1.getF() > node2.getF();
}

bool operator <=(const Node& node1, const Node& node2) {
    return node1.getF() <= node2.getF();
}

bool operator >=(const Node& node1, const Node& node2) {
    return node1.getF() >= node2.getF();
}

bool operator ==(const Node& node1, const Node& node2) {
    return node1.getPos() == node2.getPos();
}

bool operator !=(const Node& node1, const Node& node2) {
    return !(node1 == node2);
}

Node& Node::operator =(const Node& node1) {
    if (this != &node1) {
        _position = node1._position;
        _val = node1._val;
        _h = node1._h;
        _g = node1._g;
        _previousPosition = node1._previousPosition;
        _neighborsPositions = node1._neighborsPositions;
    }
    return *this;
}

/*======================================================= Implementação classe de Grafo =========================================================*/

Graph::Graph(const Map& map) : _map(map) {
    // Cria grafo com nós correspondentes às células do mapa que não são paredes, e estabelece as conexões entre os nós com base nas posições adjacentes no mapa
    for (long y = 0; y < _map.getMapYLenght(); ++y) {
        for (long x = 0; x < _map.getMapXLenght(); ++x) {
            // Obtém a posição e o valor da célula no mapa
            MapPosition pos = {y, x};
            byte value = _map(pos);
            
            // Caso a célula não sejam caminho ou saída, ou seja, seja uma parede, cria-se um nó correspondente à posição da célula e ao valor da célula, e adiciona-se ao vetor de nós do grafo
            if (value != WALL_CELL) {
                _nodes.emplace_back(Node(pos, value));
            }
        }
    }
    
    // Estabelece as conexões entre os nós, ou seja, define os vizinhos de cada nó com base nas posições adjacentes no mapa
    for (Node& node : _nodes) {
        // Extrai coordenadas da posição do nó atual
        MapPosition pos = node.getPos();
        long y = pos.first;
        long x = pos.second;
        
        // Define as movimentações possíveis (direções) a partir da posição atual do nó
        std::vector<MapPosition> directions = {
            {y, x + 1},  // right
            {y, x - 1},  // left
            {y + 1, x},  // down
            {y - 1, x}   // up
        };
        
        // Percorre as quatro direções para encontrar os vizinhos
        for(const auto& dir : directions) {
            // Se a posição é válida e se não é uma parede para adicionar como vizinho
            if(_map.positionIsValid(dir) && _map(dir) != WALL_CELL) {
                // Procura o nó correspondente à posição vizinha e adiciona como vizinho do nó atual
                for(Node& neighborNode : _nodes) {
                    // Ao encontrar o nó vizinho correspondente à posição, adiciona-se como vizinho do nó atual e sai do loop
                    if(neighborNode.getPos() == dir) {
                        node.addNeighbor(&neighborNode);
                        break;
                    }
                }
            }
        }
    }
}

Node* Graph::getNode(MapPosition pos) {
    // Se a posição é inválida, retorna nullptr
    if (!_map.positionIsValid(pos)) {
        return nullptr;
    }

    // Procura o nó correspondente à posição fornecida e retorna uma referência para ele
    for (Node& node : _nodes) {
        if (node.getPos() == pos) {
            return &node;
        }
    }

    // Retorna nullptr se o nó não for encontrado
    return nullptr; 
}

Path Graph::getExitPath(SearchAlgorithm algorithm) {
    // Caminho de volta, inicialmente vazio, pois possa ser que nenhum caminho até a saída seja de fato encontrado
    Path exitPath = {};
    MapPosition start = _map.getStart();
    MapPosition exit = _map.getExit();

    // Se a posição de início é igual à posição de saída, retorna um caminho contendo apenas a posição de início/saída
    if(start == exit){
        return {start};
    }

    // Se a posição de início ou a posição de saída são inválidas, retorna um caminho vazio
    if(!_map.positionIsValid(start) || !_map.positionIsValid(exit)){
        return {};
    }
    
    // Se o A* for escolhido, chama-se a função de busca A* para encontrar o caminho da célula de início até a célula de saída do labirinto
    if(algorithm == A_STAR_ALGORITHM){
        exitPath = this->aStarSearch(start, exit);
    } 

    // Se a busca em profundidade for escolhida, chama-se a função de busca em profundidade para encontrar o caminho da célula de início até a célula de saída do labirinto
    if(algorithm == DFS_ALGORITHM){
        exitPath = this->dfsSearch(start, exit);
    }
    
    // Retorna o caminho encontrado, ou um vetor vazio caso nenhum caminho seja encontrado
    return exitPath;
}

/*=============================================== Implementação dos algoritmos de busca A* e DFS =========================================================*/

Path Graph::aStarSearch(MapPosition start, MapPosition exit) {
    // Caminho de saída, inicialmente vazio, pois possa ser que nenhum caminho até a saída seja de fato encontrado
    Path exitPath = {};

    // Listas de nós abertos e fechados para o algoritmo A*
    std::vector<Node*> visitedNodes;
    std::set<Node*, CompareNodePointers> openNodes;

    // Obtém o nó inicial correspondente à posição de início do mapa
    Node* startNode = this->getNode(start);
    if(startNode == nullptr){
        return {};
    }

    // Obtém o nó final correspondente à posição de saída do mapa para calcular a heurística
    Node* exitNode = this->getNode(exit);
    if(exitNode == nullptr){
        return {};
    }

    // Inicializa o nó inicial com custo g=0 e heurística h
    startNode->setG(0);
    startNode->setH(distance(start, exit));
    
    // Adiciona o nó inicial à lista de nós abertos
    openNodes.insert(startNode);

    // Chama algoritmo A* recursivo para encontrar o caminho da célula de início até a célula de saída do labirinto
    this->aStarRecursive(startNode, exit, openNodes, visitedNodes);

    // Reconstrói o caminho de saída a partir do nó final encontrado
    // Percorre-se a lista de nós anteriores para reconstruir o caminho da célula de início até a célula de saída do labirinto, adicionando as posições dos nós ao caminho de saída
    Node* currentNode = exitNode;
    while(currentNode->getPrevious() != MapPosition{-1, -1}){
        exitPath.push_back(currentNode->getPos());
        currentNode = this->getNode(currentNode->getPrevious());
    }
    
    // Adiciona o nó inicial ao caminho
    exitPath.push_back(currentNode->getPos());
    
    // Inverte o caminho para que esteja na ordem correta (do início até a saída)
    std::reverse(exitPath.begin(), exitPath.end());

    // Se o nó inicial ou o nó final são inválidos, retorna um caminho vazio
    return exitPath;
}

void Graph::aStarRecursive(Node* currentNode, MapPosition exit, std::set<Node*, CompareNodePointers>& openNodes, std::vector<Node*>& visitedNodes) {
    // Se o nó atual é o nó de saída, adiciona-se o nó atual à lista de nós fechados e retorna
    if(currentNode->getPos() == exit){
        visitedNodes.push_back(currentNode);
        return;
    }

    // Percorre nos vizinhos do nó atuale para cada vizinho, calcula-se o custo total f = g + h do nó vizinho
    for(auto neighborPos : currentNode->getNeighbors()){
        // Obtém o nó vizinho correspondente à posição do vizinho
        Node* neighbor = this->getNode(neighborPos);
        if(neighbor == nullptr){
            continue;
        }
        
        // Se o nó vizinho já está na lista de nós fechados, ignora-se o nó vizinho e continua para o próximo vizinho
        if(std::find(visitedNodes.begin(), visitedNodes.end(), neighbor) != visitedNodes.end()){
            continue;
        }
        
        // Valores de custo para novo nó vizinho, a partir da chegada pelo nó atual, e custo heurístico para o nó vizinho
        long g = currentNode->getG() + PATH_COST_SCALE;
        long h = distance(neighbor->getPos(), exit);
        long f = g + h;
        
        // Se o  nó vizinho está na lista de abertos, verifica-se se o custo total f é vai ser menor ou não caso o caminho para esse nó seja atualizado
        // Caso sim, o nó prévio do vizinho é atualizado para o nó atual, e o custo g do nó vizinho é atualizado para o custo g do nó atual mais o custo de movimentação
        auto neighbotOpenIt = std::find_if(openNodes.begin(), openNodes.end(), [&](Node* node){
            return node == neighbor;
        });
        if(neighbotOpenIt != openNodes.end()){
            // Se o novo custo for maior/igual que o antigo custo do nó vizinho, ignora-se o nó vizinho e continua para o próximo vizinho
            if((*neighbotOpenIt)->getF() <= f){
                continue;
            }
            
            // Caso o novo custo seja menor ao antigo custo do nó vizinho, remove-se o nó vizinho da lista de nós abertos para que ele seja atualizado com o novo custo mais baixo
            openNodes.erase(neighbotOpenIt);
        }
        
        // Atualiza nó prévio, custo g e custo h do nó vizinho
        neighbor->setPrevious(currentNode);
        neighbor->setG(g);
        neighbor->setH(h);

        // Adiciona-se o nó vizinho à lista de nós abertos para que ele seja visitado posteriormente
        openNodes.insert(neighbor);
    }

    // Coloca nó atual na lista de nós fechados para que ele não seja visitado novamente
    visitedNodes.push_back(currentNode);

    // Tira nó atual da lista de nós abertos
    auto currentOpenNodeIt = std::find_if(openNodes.begin(), openNodes.end(), [&](Node* node){
        return node == currentNode;
    });
    openNodes.erase(currentOpenNodeIt);

    // Se a lista de nós abertos está vazia, retorna, pois não há mais nós para visitar e o caminho até a saída não foi encontrado
    if(openNodes.empty()){
        return;
    }

    // Obtém o próximo nó a ser visitado, que é o nó com o menor custo total (f) na lista de nós abertos, e chama-se recursivamente a função A* para o próximo nó a ser visitado
    Node* nextNode = *(openNodes.begin());
    this->aStarRecursive(nextNode, exit, openNodes, visitedNodes);
}

Path Graph::dfsSearch(MapPosition start, MapPosition exit) {
    // Caminho de saída, inicialmente vazio, pois possa ser que nenhum caminho até a saída seja de fato encontrado
    Path exitPath = {};

    // Listas de nós abertos e fechados para o algoritmo A*
    std::vector<Node*> visitedNodes;

    // Obtém o nó inicial correspondente à posição de início do mapa
    Node* startNode = this->getNode(start);
    if(startNode == nullptr){
        return {};
    }

    // Obtém o nó final correspondente à posição de saída do mapa para calcular a heurística
    Node* exitNode = this->getNode(exit);
    if(exitNode == nullptr){
        return {};
    }

    // Inicializa o nó inicial com custo g=0 e heurística h
    startNode->setG(0);
    startNode->setH(distance(start, exit));
    

    // Chama algoritmo A* recursivo para encontrar o caminho da célula de início até a célula de saída do labirinto
    this->dfsRecursive(startNode, exit, visitedNodes);

    // Reconstrói o caminho de saída a partir do nó final encontrado
    // Percorre-se a lista de nós anteriores para reconstruir o caminho da célula de início até a célula de saída do labirinto, adicionando as posições dos nós ao caminho de saída
    Node* currentNode = exitNode;
    while(currentNode->getPrevious() != MapPosition{-1, -1}){
        exitPath.push_back(currentNode->getPos());
        currentNode = this->getNode(currentNode->getPrevious());
    }
    
    // Adiciona o nó inicial ao caminho
    exitPath.push_back(currentNode->getPos());
    
    // Inverte o caminho para que esteja na ordem correta (do início até a saída)
    std::reverse(exitPath.begin(), exitPath.end());

    // Se o nó inicial ou o nó final são inválidos, retorna um caminho vazio
    return exitPath;
}

void Graph::dfsRecursive(Node* currentNode, MapPosition exit, std::vector<Node*>& visitedNodes) {
    // Coloca nó atual na lista de nós visitados para que ele não seja visitado novamente
    visitedNodes.push_back(currentNode);
    
    // Se o nó atual é o nó de saída, adiciona-se o nó atual à lista de nós visitados e retorna
    if(currentNode->getPos() == exit){
        return;
    }

    // Percorre nos vizinhos do nó atuale para cada vizinho, calcula-se o custo total f = g + h do nó vizinho
    for(auto neighborPos : currentNode->getNeighbors()){
        // Obtém o nó vizinho correspondente à posição do vizinho
        Node* neighbor = this->getNode(neighborPos);
        if(neighbor == nullptr){
            continue;
        }
        
        // Se o nó vizinho já está na lista de nós fechados, ignora-se o nó vizinho e continua para o próximo vizinho
        if(std::find(visitedNodes.begin(), visitedNodes.end(), neighbor) != visitedNodes.end()){
            continue;
        }
        
        // Atualiza nó prévio, custo g e custo h do nó vizinho
        neighbor->setPrevious(currentNode);

        this->dfsRecursive(neighbor, exit, visitedNodes);
    }
}

