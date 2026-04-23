#include "map.h"
#include <math.h>
#include <iostream>

long distance(MapPosition pos1, MapPosition pos2) {
	return (long)(PATH_COST_SCALE * (abs(pos2.first - pos1.first) + abs(pos2.second - pos1.second)));
}

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

