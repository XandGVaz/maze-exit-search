#include "map.h"
#include <math.h>
#include <iostream>


namespace Maping {

	// ============ Map IMPLEMENTATION ============

	bool Map::positionIsValid(MapPosition pos) {
		return (pos.first >= 0 && pos.first < _mapYLenght && 
				pos.second >= 0 && pos.second < _mapXLenght);
	}


	void Map::toFilledMap(CellValue value) {
		for(long y = 0; y < _mapYLenght; y++) {
			for(long x = 0; x < _mapXLenght; x++) {
				_cells[y][x] = value;
			}
		}
	}

	byte& Map::operator()(MapPosition pos) {
		return _cells[pos.first][pos.second];
	}

	byte& Map::operator()(long y, long x) {
		return _cells[y][x];
	}

	bool Map::setStart(MapPosition pos) {
		if(positionIsValid(pos)) {
			_start = pos;
			return true;
		}
		return false;
	}

	bool Map::setExit(MapPosition pos) {
		if(positionIsValid(pos)) {
			_exit = pos;
			return true;
		}
		return false;
	}


	Map& Map::operator=(const Map& map2) {
		if(this != &map2) {
			_mapXLenght = map2._mapXLenght;
			_mapYLenght = map2._mapYLenght;
			_cells = map2._cells;
		}
		return *this;
	}

	// ============ UTILITY FUNCTIONS ============

	// Map getEmptyMap(long map_x_lenght, long map_y_lenght){
	// 	// Aloca memória para a matriz de bytes
	// 	Map emptyMap = new byte*[map_y_lenght];
	// 	for(long i = 0; i < map_y_lenght; i++){
	// 		emptyMap[i] = new byte[map_x_lenght];
	// 	}
	// 	// Preenche a matriz de bytes com paredes (1) nas bordas do labirinto e caminho (0) no restante das células
	// 	for(long x = 0; x < map_x_lenght; x++){
	// 		for(long y = 0; y < map_y_lenght; y++){
	// 			// Paredes Marrons nas bordas
	// 			if(x == 0 || x == map_x_lenght-1 || y == 0 || y == map_y_lenght-1)
	// 				emptyMap[y][x] = 1;
	// 			// Caminho
	// 			else
	// 				emptyMap[y][x] = 0;
	// 		}
	// 	}
	// 	return emptyMap;
	// }

	// Map getFilledMap(long map_x_lenght, long map_y_lenght) {
	// 	// Aloca memória para a matriz de bytes
	// 	Map filledMap = new byte*[map_y_lenght];
	// 	for(long i = 0; i < map_y_lenght; i++){
	// 		filledMap[i] = new byte[map_x_lenght];
	// 	}
	// 	// Preenche a matriz de bytes com paredes (1) em todas as células
	// 	for(long x = 0; x < map_x_lenght; x++){
	// 		for(long y = 0; y < map_y_lenght; y++){
	// 			// Paredes Marrons em todas as células
	// 			filledMap[y][x] = 1;
	// 		}
	// 	}
	// 	return filledMap;
	// }

	// long distance(MapPosition pos1, MapPosition pos2){
	// 	return (long)(PATH_COST_SCALE * sqrt(pow(pos2.first - pos1.first, 2) + pow(pos2.second - pos1.second, 2)));
	// }

	// byte getMapValue(Map map, MapPosition position){
	// 	return map[position.first][position.second];
	// }

	// void setMapValue(Map map, MapPosition position, byte value){
	// 	map[position.first][position.second] = value;
	// }

	// MapNode createMapNode(Map map, MapPosition position, const MapNode* previousNode, MapPosition finalPosition){
	// 	MapNode node;
	// 	node.position = position;
	// 	node.previousNodePosition = {-1, -1};
	// 	node.g = 0;
	// 	if(previousNode != nullptr){
	// 		node.previousNodePosition = previousNode->position;
	// 		node.g = previousNode->g + PATH_COST_SCALE;
	// 	}
	// 	node.h = distance(position, finalPosition);
	// 	node.mapValue = getMapValue(map, position);
	// 	return node;
	// }

	// MapPosition stochastic(Map map, const MapNode* actualNode, std::set<MapNode, CompareNode> &openNodes, std::vector<MapNode> &closeNodes, MapPosition finalPosition){
	// 	// Se o nó atual é igual ao nó final, a função retorna, indicando que o caminho foi encontrado
	// 	if(actualNode->position == finalPosition){
	// 		std::cout << "Caminho encontrado!" << std::endl;
	// 		closeNodes.push_back(*actualNode);
	// 		return actualNode->position;
	// 	}

	// 	// Vetor de nós vizinhos do nó atual, ou seja, os nós que estão adjacentes ao nó atual e que podem ser visitados a partir do nó atual
	// 	std::vector<MapNode> neighbors;
		
	// 	// Posições do nó atual, do nó final e das células vizinhas (acima, abaixo, à direita e à esquerda) do nó atual
	// 	MapPosition actualPosition = actualNode->position;
	// 	MapPosition abovePosition = {actualPosition.first + 1, actualPosition.second};
	// 	MapPosition belowPosition = {actualPosition.first - 1, actualPosition.second};
	// 	MapPosition rightPosition = {actualPosition.first, actualPosition.second + 1};
	// 	MapPosition leftPosition  = {actualPosition.first, actualPosition.second - 1};

	// 	// Para cada célula vizinha do nó atual, se a célula vizinha é um caminho (valor 0 no mapa), cria-se um nó para a célula vizinha e adiciona-se o nó ao vetor de nós vizinhos
	// 	if(getMapValue(map, abovePosition) != 1){
	// 		neighbors.push_back(createMapNode(map, abovePosition, actualNode, finalPosition));
	// 	}
	// 	if(getMapValue(map, belowPosition) != 1){
	// 		neighbors.push_back(createMapNode(map, belowPosition, actualNode, finalPosition));
	// 	}
	// 	if(getMapValue(map, rightPosition) != 1){
	// 		neighbors.push_back(createMapNode(map, rightPosition, actualNode, finalPosition));
	// 	}
	// 	if(getMapValue(map, leftPosition) != 1){
	// 		neighbors.push_back(createMapNode(map, leftPosition, actualNode, finalPosition));
	// 	}

	// 	// Percorre-se o vetor de nós vizinhos do nó atual
	// 	for(auto neighbor = neighbors.begin(); neighbor != neighbors.end(); neighbor++){
	// 		// Se o nó vizinho já está na lista de nós fechados, parte-se para o próximo nó vizinho
	// 		if(std::find_if(closeNodes.begin(), closeNodes.end(), [&](const MapNode& node){
	// 			return node.position == neighbor->position;
	// 		}) != closeNodes.end()){
	// 			continue;
	// 		}

	// 		// Se o nó vizinho já está na lista de nós abertos, verifica-se se o custo do caminho para o nó vizinho é menor do que o custo do caminho para o nó vizinho
	// 		// através do nó atual. Se for menor, remove-se o nó vizinho da lista de nós abertos para que ele seja atualizado com o novo custo mais baixo
	// 		auto openNodeIt = std::find_if(openNodes.begin(), openNodes.end(), [&](const MapNode& node){
	// 			return node.position == neighbor->position;
	// 		});
	// 		if(openNodeIt != openNodes.end()){
	// 			if(openNodeIt->g + openNodeIt->h < neighbor->g + neighbor->h){
	// 				continue;
	// 			}
	// 			openNodes.erase(openNodeIt);
	// 		}

	// 		// Adiciona-se o nó vizinho à lista de nós abertos para que ele seja visitado posteriormente
	// 		openNodes.insert(*neighbor);
	// 	}

	// 	// Adiciona-se o nó atual à lista de nós fechados para que ele não seja visitado novamente
	// 	closeNodes.push_back(*actualNode);

	// 	// Remove-se o nó atual da lista de nós abertos
	// 	auto currentNodeIt = std::find_if(openNodes.begin(), openNodes.end(), [&](const MapNode& node){
	// 		return node.position == actualNode->position;
	// 	});
	// 	if(currentNodeIt != openNodes.end()){
	// 		openNodes.erase(currentNodeIt);
	// 	}

	// 	// Seleciona-se o próximo nó a ser visitado, que é o nó com o menor custo total (g + h) na lista de nós abertos
	// 	if(openNodes.empty()){
	// 		return MapPosition{-1, -1};
	// 	}

	// 	// Copia-se o nó para evitar referências inválidas após modificações no set
	// 	MapNode proxNode = *openNodes.begin();

	// 	// Chama-se recursivamente a função stochastic para o próximo nó a ser visitado
	// 	return stochastic(map, &proxNode, openNodes, closeNodes, finalPosition);
	// }

	// Path getExitPath(Map map, MapPosition start, MapPosition final){
	// 	// Vetores de nós abertos e fechados para o algoritmo A*
	// 	std::set<MapNode, CompareNode> openNodes;
	// 	std::vector<MapNode> closedNodes;

	// 	// Nó inicial e nó final do algoritmo A*
	// 	MapNode startNode = createMapNode(map, start, nullptr, final);
		
	// 	// Insere nó inicial na lista de nós abertos
	// 	openNodes.insert(startNode);
		
	// 	// Insere o nó inicial na lista de nós abertos
	// 	MapPosition finalPosition = stochastic(map, &startNode, openNodes, closedNodes, final);

	// 	// Vetor de posições do caminho da célula de início até a célula de saída do labirinto
	// 	Path path;

	// 	// Se a posição final é inválida, ou seja, não foi encontrado um caminho, retorna um vetor vazio
	// 	if(finalPosition.first == -1 && finalPosition.second == -1){
	// 		std::cout << "Caminho não encontrado!" << std::endl;
	// 		return {};
	// 	}

	// 	// Percorre-se a lista de nós fechados para encontrar o caminho da célula de início até a célula de saída do labirinto, seguindo as posições dos nós anteriores
	// 	MapPosition currentPosition = finalPosition;
	// 	for(auto it = closedNodes.rbegin(); it != closedNodes.rend(); it++){
	// 		if(it->position == currentPosition){
	// 			path.push_back(it->previousNodePosition);
	// 			currentPosition = it->previousNodePosition;
	// 		}
	// 	}

	// 	return path;
	// }

}
