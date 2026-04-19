#include "maze.h"
#include <random>
#include <iostream>
#include <set>

Maze::Maze(long map_x_lenght, long map_y_lenght){
	_mazeX = map_x_lenght;
	_mazeY = map_y_lenght;
	_mazeMap = getEmptyMap(map_x_lenght, map_y_lenght);
	_mazeStart = {map_y_lenght/2, map_x_lenght/2};
}

Maze::~Maze(){
	for(long i = 0; i < _mazeY; i++){
		delete[] _mazeMap[i];
	}
	delete[] _mazeMap;
}

void Maze::createPaths(long x_origin, long y_origin, std::vector<std::pair<MapPosition,MapPosition>> &possibOuts){

	// Número que representa a direção e sentido da próxima célula
	long d = 0;

	// Vetor de possíveis direções da próxima célula
	std::vector<int> v{0,1,2,3};

	// Motor com semente gerada por `rd`.
	std::random_device rd;
	std::mt19937 R(rd());

	// Embaralha o vetor de direções para aumentar aleatoriedade do labirinto
	std::shuffle(v.begin(), v.end(), R);

	// marca posição atual como caminho
	_mazeMap [y_origin][x_origin] = 0;

	// Busca em profundidade em células vizinhas
	for(long i = 0; i < 4; i++){

		// x e y da célula de origem
		long x = x_origin;
		long y = y_origin;

		// Direção atual do for
		d = v[i];

		// De acordo coma a direção e sentido da célula vizinha, move-se x e y
		switch(d){
			case 0: x += 2; break;
			case 1: x -= 2; break;
			case 2: y += 2; break;
			case 3: y -= 2; break;
		}
		
		// Se célula vizinha conhecidir com parede ou estiver fora do labirinto, parte-se para próxima
		if(x <= 0 || x >= _mazeX -1 || y <= 0 || y >= _mazeY -1){
			
			// Flag para o caso em que a célula vizinha está fora do labirinto
			bool flag = false;
			if(x < 0 || x > _mazeX -1 || y < 0 || y > _mazeY -1) flag = true;
			
			// Par da saída (célula do meio entre a atual e a vizinha, célula vizinha)
			std::pair<MapPosition,MapPosition> out;

			// De acordo com a direção e sentido da célula vizinha, adiciona-se a célula do meio
			//entre a atual e a vizinha, no primeiro elemento do par da possível saída
			switch(d){
				case 0: 
						out.first.first = y; out.first.second = x -1;
						break;
				case 1: 
						out.first.first = y; out.first.second = x +1;
						break;
				case 2:  
						out.first.first = y -1; out.first.second = x;
						break;
				case 3:  
						out.first.first = y +1; out.first.second = x;
						break;
			}

			// Se a célula vizinha está fora do labirinto, a segunda parte é igual à célula do meio 
			out.second.first = flag ? out.first.first : y; 
			out.second.second = flag ? out.first.second : x;
			
			// Adiciona saída ao vetor de possíveis saídas
			possibOuts.push_back(out);
			
			// Continua para a próxima célula vizinha
			continue;
		}

		// Se a célula vizinha já foi vizitada, parte-se para a próxima
		if(_mazeMap[y][x] == 0)
			continue;

		// Caso contrário, célula entre a atual e a vizinha (2 unidades de distância), marcamos
		//célula no meio entre as duas como caminho
		switch(d){
			case 0: _mazeMap[y][x-1] = 0; break;
			case 1: _mazeMap[y][x+1] = 0; break;
			case 2: _mazeMap[(y-1)][x] = 0; break;
			case 3: _mazeMap[(y+1)][x] = 0; break;
		}
		
		// Busca em profundidade da célula vizinha
		createPaths(x, y, possibOuts);	
	}

}

MapPosition Maze::toRandomMaze(){
	// Deleta o labirinto atual
	for(long i = 0; i < _mazeY; i++){
		delete[] _mazeMap[i];
	}
	delete[] _mazeMap;

	// Cria-se um labirinto somente com paredes ( _maze[j] != 0 para todo j )
	_mazeMap = getFilledMap(_mazeX, _mazeY);

	// Vetor de possíveis saídas do labirinto
	std::vector<std::pair<MapPosition,MapPosition>> possibOuts;
		
	// começa busca em profundidade a partir do meio do labirinto
	createPaths(_mazeX/2, _mazeY/2, possibOuts);

	// Motor com semente gerada por `rd`.
	std::random_device rd;
	std::mt19937 R(rd());

	// Distribuição de números inteiros entre 0 e o tamanho da lista de saídas possíveis
	std::uniform_int_distribution<int> dist(0, possibOuts.size()-1);
	
	// Escolhe uma saída aleatória (formada por um par) devido a distância entre as células vizinhas
	std::pair<MapPosition,MapPosition> randomOut = possibOuts[dist(R)];

	// Marca a saída como caminho
	_mazeMap[randomOut.first.first][randomOut.first.second] = 7;
	_mazeMap[randomOut.second.first][randomOut.second.second] = 7;

	// Retorna índice da célula de saída do labirinto
	return randomOut.second;
}

Map Maze::createMaze(){
	_mazeExit = this->toRandomMaze();
	return this->getMazeMap();
}

Maze& Maze::operator =(const Maze& maze2){
	// Copia o tamanho do labirinto em X e Y e inicializa o mapa do labirinto como um mapa vazio
	_mazeX = maze2._mazeX;
	_mazeY = maze2._mazeY;
	_mazeMap = getEmptyMap(_mazeX, _mazeY);

	// Copia o mapa do labirinto de maze2 para o labirinto atual
	for(long x = 0; x < _mazeX; x++){
		for(long y = 0; y < _mazeY; y++){
			_mazeMap[y][x] = maze2._mazeMap[y][x];
		}
	}
	
	// Copia a posição da saída do labirinto de maze2 para o labirinto atual
	_mazeExit = maze2._mazeExit;

	// Retorna referência para o objeto da classe Maze que recebeu a cópia
	return *this;
}

void Maze::ptintMaze(){
	for(long y = 0; y < _mazeY; y++){
		for(long x = 0; x < _mazeX; x++){
			if (y == _mazeStart.first && x == _mazeStart.second) {
				std::cout << "S"; // Símbolo de início
			} else if (_mazeMap[y][x] == 1)
				std::cout << "█"; // Parede
			else if (_mazeMap[y][x] == 0)
				std::cout << " "; // Caminho
			else if (_mazeMap[y][x] == 7)
				std::cout << "E"; // Saída
			else
				std::cout << "?"; // Valor desconhecido
		}
		std::cout << std::endl;
	}
}

struct CompareNode {
    bool operator()(const MapNode& a, const MapNode& b) const {
        return (a.g + a.h) < (b.g + b.h);
    }
};


MapNode createMapNode(Map map, MapPosition position, const MapNode* previousNode, MapPosition finalPosition){
	MapNode node;
	node.position = position;
	node.previousNode = nullptr;
	node.g = 0;
	if(previousNode != nullptr){
		node.g = previousNode->g + PATH_COST_SCALE;
	}
	node.h = distance(position, finalPosition);
	node.mapValue = getMapValue(map, position);
	return node;
}

void stochastic(Map map, const MapNode* actualNode, std::set<MapNode, CompareNode> &openNodes, std::vector<MapNode> &closeNodes, const MapNode* finalNode){
	
	// Se a lista de nós abertos está vaziao, e a função retorna sem encontrar um caminho
	if(openNodes.empty()){
		return;
	}

	// Se o nó atual é igual ao nó final, a função retorna, indicando que o caminho foi encontrado
	if(actualNode->position == finalNode->position){
		return;
	}

	// Vetor de nós vizinhos do nó atual, ou seja, os nós que estão adjacentes ao nó atual e que podem ser visitados a partir do nó atual
	std::vector<MapNode> neighbors;
	
	// Posições do nó atual, do nó final e das células vizinhas (acima, abaixo, à direita e à esquerda) do nó atual
	MapPosition actualPosition = actualNode->position;
	MapPosition finalPosition = finalNode->position;
	MapPosition abovePosition = {actualPosition.first + 1, actualPosition.second};
	MapPosition belowPosition = {actualPosition.first - 1, actualPosition.second};
	MapPosition rightPosition = {actualPosition.first, actualPosition.second + 1};
	MapPosition leftPosition  = {actualPosition.first, actualPosition.second - 1};

	// Para cada célula vizinha do nó atual, se a célula vizinha é um caminho (valor 0 no mapa), cria-se um nó para a célula vizinha e adiciona-se o nó ao vetor de nós vizinhos
	if(getMapValue(map, abovePosition) == 0){
		neighbors.push_back(createMapNode(map, abovePosition, actualNode, finalPosition));
	}
	if(getMapValue(map, belowPosition) == 0){
		neighbors.push_back(createMapNode(map, belowPosition, actualNode, finalPosition));
	}
	if(getMapValue(map, rightPosition) == 0){
		neighbors.push_back(createMapNode(map, rightPosition, actualNode, finalPosition));
	}
	if(getMapValue(map, leftPosition) == 0){
		neighbors.push_back(createMapNode(map, leftPosition, actualNode, finalPosition));
	}

	// Percorre-se o vetor de nós vizinhos do nó atual
	for(auto neighbor = neighbors.begin(); neighbor != neighbors.end(); neighbor++){
		// Se o nó vizinho já está na lista de nós fechados, parte-se para o próximo nó vizinho
		if(std::find(closeNodes.begin(), closeNodes.end(), neighbor) != closeNodes.end()){
			continue;
		}

		// Se o nó vizinho já está na lista de nós abertos, verifica-se se o custo do caminho para o nó vizinho é menor do que o custo do caminho para o nó vizinho
		// através do nó atual. Se for menor, remove-se o nó vizinho da lista de nós abertos para que ele seja atualizado com o novo custo mais baixo
		auto openNodeIt = openNodes.find(*neighbor);
		if(openNodeIt != openNodes.end()){
			if(openNodeIt->g + openNodeIt->h <= neighbor->g + neighbor->h){
				continue;
			}
			openNodes.erase(openNodeIt);
		}

		// Adiciona-se o nó vizinho à lista de nós abertos para que ele seja visitado posteriormente
		openNodes.insert(*neighbor);
	}

	// Adiciona-se o nó atual à lista de nós fechados para que ele não seja visitado novamente
	closeNodes.push_back(*actualNode);

	// Seleciona-se o próximo nó a ser visitado, que é o nó com o menor custo total (g + h) na lista de nós abertos
	auto proxNodeIt = openNodes.begin();
	const MapNode* proxNode = &(*proxNodeIt);

	// Chama-se recursivamente a função stochastic para o próximo nó a ser visitado
	stochastic(map, &(*openNodes.begin()), openNodes, closeNodes, finalNode);
}

Path getExitPath(Map map, MapPosition start, MapPosition final){
	// Vetores de nós abertos e fechados para o algoritmo A*
	std::set<MapNode, CompareNode> openNodes;
	std::vector<MapNode> closedNodes;

	// Nó inicial e nó final do algoritmo A*
	MapNode startNode = createMapNode(map, start, nullptr, final);
	MapNode finalNode = createMapNode(map, start, nullptr, final);
	
	// Insere nó inicial na lista de nós abertos
	openNodes.insert(startNode);

	// Insere o nó inicial na lista de nós abertos
	stochastic(map, &startNode, openNodes, closedNodes, &finalNode);

	// Vetor de posições do caminho da célula de início até a célula de saída do labirinto
	Path path;

	// Recupera melhor caminho recuperando-o a partir do nó final, seguindo os nós anteriores até chegar no nó inicial, 
	//e adicionando as posições dos nós ao vetor de posições do caminho 
	for(const MapNode* node = &finalNode; node != nullptr; node = node->previousNode){
		path.push_back(node->position);
	}
}

