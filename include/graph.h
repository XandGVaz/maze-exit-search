#pragma once

#include "map.h"
#include <vector>

using namespace Maping;

typedef enum{
    A_STAR_ALGORITHM = 0U,
    DFS_ALGORITHM = 1
}SearchAlgorithm;

class Node{
    MapPosition _position;
    std::vector<MapPosition> _neighborsPositions;
    MapPosition _previousPosition;
    byte _val;
    long _h;
    long _g;
public:
    Node(MapPosition pos, byte value);

    void addNeighbor(Node* neighbor);

    void setPrevious(Node* previous);
    void setH(long h);
    void setG(long g);

    MapPosition getPos(){ return _position; }
    std::vector<MapPosition>& getNeighbors(){ return _neighborsPositions; }
    MapPosition getPrevious(){ return _previousPosition; }
    long getH(){ return _h; }
    long getG(){ return _g; }
    long getF(){ return _g + _h; }

    friend bool operator <(const Node& node1, const Node& node2);
    friend bool operator >(const Node& node1, const Node& node2);
    friend bool operator ==(const Node& node1, const Node& node2);
    Node& operator =(const Node& node1);
};

class Graph{
    Map _map;
    std::vector<Node> _nodes;
public:
    Graph(Map map);
    ~Graph();

    std::vector<Node>& getNodes();
    Node& getNode(MapPosition pos);
    
    Path getExitPath(MapPosition start, MapPosition final, SearchAlgorithm algorithm);
};