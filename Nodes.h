#pragma once

#include <vector>
#include "glm/glm.hpp"
#include <string>

struct Node;

struct Edge { //connections between nodes

    Edge() { target = nullptr; cost = 0; } //the basic edge has no target, or any traversal cost
    Edge(Node* _target, float _cost) : target(_target), cost(_cost) {}//a created edge will have a target node, and the cost of traversing it

    Node* target;//where the edge connects to
    float cost; // how hard it is to traverse across this edge
};


struct Node { // our positions on the map
    glm::vec2 position;//our posiitons on the map represented as x,y co-ordinates
    std::vector<Edge> connections;//any edges that connect this node to another
    

    Node(float x, float y, float score) { position.x = x, position.y = y, gScore = score; }//create a node at a given co-ordinate
    Node() {}

    std::string tileType;
    float gScore;//the current cost required to get to this node from a point
    Node* previous;//the node before this one in a path
    

    void ConnectTo(Node* other, float cost)//connect this node to another node via an edge
    {
        connections.push_back(Edge(other, cost));
    }
};