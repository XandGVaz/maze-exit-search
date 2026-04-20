#include "map.h"

namespace Maping {

	Map getEmptyMap(long map_x_lenght, long map_y_lenght){
		// Aloca memória para a matriz de bytes
		Map emptyMap = new byte*[map_y_lenght];
		for(long i = 0; i < map_y_lenght; i++){
			emptyMap[i] = new byte[map_x_lenght];
		}
		
		// Preenche a matriz de bytes com paredes (1) nas bordas do labirinto e caminho (0) no restante das células
		for(long x = 0; x < map_x_lenght; x++){
			for(long y = 0; y < map_y_lenght; y++){
				// Paredes Marrons nas bordas
				if(x == 0 || x == map_x_lenght-1 || y == 0 || y == map_y_lenght-1)
					emptyMap[y][x] = 1;
				// Caminho
				else
					emptyMap[y][x] = 0;
			}
		}
		return emptyMap;
	}

	Map getFilledMap(long map_x_lenght, long map_y_lenght) {
		// Aloca memória para a matriz de bytes
		Map filledMap = new byte*[map_y_lenght];
		for(long i = 0; i < map_y_lenght; i++){
			filledMap[i] = new byte[map_x_lenght];
		}

		// Preenche a matriz de bytes com paredes (1) em todas as células
		for(long x = 0; x < map_x_lenght; x++){
			for(long y = 0; y < map_y_lenght; y++){
				// Paredes Marrons em todas as células
				filledMap[y][x] = 1;
			}
		}
		return filledMap;
	}
};