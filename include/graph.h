#pragma once

#include "map.h"
#include <vector>

class Node{
    MapPosition _position;
    std::vector<MapPosition> _neighborsPositions;
    MapPosition _previousPosition;
    long _h;
    long _g;
    long _f;
public:
    Node(MapPosition pos, long h, long g);

    void setPrevious(Node* previous);
    void addNeighbor(Node* neighbor);

    MapPosition getPos();
    std::vector<Node*> getNeighbors();
    Node* getPrevious();
    long getH();
    long getG();
    long getF();
}

class Graph{
    Map _map;
    long _mapX;
    long _mapY;
    std::vector<Node> _nodes;
public:
    Graph(Map map, long map_X_lenght, long map_Y_lenght);
    ~Graph();
    std::vector<MapPosition> getNeighbors(MapPosition pos);
    bool isExit(MapPosition pos);
    bool isValid(MapPosition pos);
}