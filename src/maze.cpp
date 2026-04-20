#include "maze.h"
#include <random>
#include <iostream>
#include <set>

void Maze::createPaths(long yOrigin, long xOrigin, std::vector<std::pair<MapPosition,MapPosition>> &possibOuts){
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
	MapPosition currentPos = {yOrigin, xOrigin};
	_mazeMap(currentPos) = 0;

	// Busca em profundidade em células vizinhas
	for(long i = 0; i < 4; i++){

		// x e y da célula de origem
		long x = xOrigin;
		long y = yOrigin;

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
		if(x <= 0 || x >= _mazeMap.getMapXLenght() -1 || y <= 0 || y >= _mazeMap.getMapYLenght() -1){
			
			// Flag para o caso em que a célula vizinha está fora do labirinto
			bool flag = false;
			if(x < 0 || x > _mazeMap.getMapXLenght() -1 || y < 0 || y > _mazeMap.getMapYLenght() -1) flag = true;
			
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
		if(_mazeMap(y,x) == 0)
			continue;

		// Caso contrário, célula entre a atual e a vizinha (2 unidades de distância), marcamos
		//célula no meio entre as duas como caminho
		switch(d){
			case 0: _mazeMap(y, x-1) = 0; break;
			case 1: _mazeMap(y, x+1) = 0; break;
			case 2: _mazeMap(y-1, x) = 0; break;
			case 3: _mazeMap(y+1, x) = 0; break;
		}
		
		// Busca em profundidade da célula vizinha
		createPaths(y, x, possibOuts);	
	}

}

MapPosition Maze::toRandomMaze(){
	// Cria-se um labirinto somente com paredes ( _maze[j] != 0 para todo j )
	_mazeMap.toFilledMap(WALL_CELL);

	// Vetor de possíveis saídas do labirinto
	std::vector<std::pair<MapPosition,MapPosition>> possibOuts;
		
	// começa busca em profundidade a partir do início do labirinto, que é o meio do mapa, e armazena as possíveis saídas do labirinto em um vetor de pares de posições
	long xOrigin = _mazeMap.getStart().second;
	long yOrigin = _mazeMap.getStart().first;
	createPaths(yOrigin, xOrigin, possibOuts);

	// Verifica se há saídas disponíveis
	if(possibOuts.empty()){
		// Se não há saídas, retorna uma posição padrão na borda
		return {_mazeMap.getMapXLenght() - 2, _mazeMap.getMapYLenght() - 2};
	}

	// Motor com semente gerada por `rd`.
	std::random_device rd;
	std::mt19937 R(rd());

	// Distribuição de números inteiros entre 0 e o tamanho da lista de saídas possíveis
	std::uniform_int_distribution<int> dist(0, possibOuts.size()-1);
	
	// Escolhe uma saída aleatória (formada por um par) devido a distância entre as células vizinhas
	std::pair<MapPosition,MapPosition> randomOut = possibOuts[dist(R)];

	// Marca a saída como caminho
	_mazeMap(randomOut.first) = EXIT_CELL;
	_mazeMap(randomOut.second) = EXIT_CELL;

	// Marca a posição de saída do labirinto
	_mazeMap.setExit(randomOut.second);

	// Retorna índice da célula de saída do labirinto 
	return randomOut.second;
}

Map& Maze::createMaze(){
	// Gera um labirinto aleatório e retorna o mapa do labirinto gerado
	this->toRandomMaze();

	// Retorna o mapa do labirinto gerado, representado por uma matriz de bytes
	return this->getMazeMap();
}

Maze& Maze::operator =(const Maze& maze2){
	// Copia o mapa
	_mazeMap = maze2._mazeMap;

	// Retorna referência para o objeto da classe Maze que recebeu a cópia
	return *this;
}

void Maze::ptintMaze(Path exitPath) {
	// Flag para o caso em que o caminho de saída é vazio
	bool emptyExitPath = exitPath.empty();

	// Par da posição atual do for
	MapPosition currentPos;
	for(long y = 0; y < _mazeMap.getMapYLenght(); y++){
		for(long x = 0; x < _mazeMap.getMapXLenght(); x++){
			// Atualiza a posição atual do for
			currentPos = {y, x};

			// Imprime conforme o valor de cada célula do labirinto
			if(currentPos == _mazeMap.getStart()){
				std::cout << "S"; // Símbolo de início
				continue;
			}
			if(!emptyExitPath){
				if(std::find(exitPath.begin(), exitPath.end(), currentPos) != exitPath.end()){
					std::cout << "x"; // Caminho da saída
					continue;
				}
			}
			if(_mazeMap(currentPos) == PATH_CELL){
				std::cout << " "; // Caminho
				continue;
			}
			if(_mazeMap(currentPos) == WALL_CELL){
				std::cout << "█"; // Parede
				continue;
			}
			if(_mazeMap(currentPos) == EXIT_CELL){
				std::cout << "E"; // Saída
				continue;
			}
			std::cout << "?"; // Valor desconhecido
		}
		std::cout << std::endl;
	}
}

