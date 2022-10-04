#pragma once
#include "Nodes.h"
#include <string>
#include "raylib.h"
#include "MapObject.h"
#include "Lever.h"
#include "Princess.h"

class NodeMap
{
private:

	int m_width;//x position
	int m_height;//y position
	float m_cellSize;//size of map cells

	Node** m_nodes;//every node in the map

	int numberOfGemPositions = 10;//10 maximum places it's okay to spawn gems
	std::vector<glm::vec2> gemPositions;//a vector containing a list of okay places to spawn a gem

	Lever* lever;//the lever object found in the map
	glm::vec2 leverPosition;//There's only 1 lever, so no need to put it in a vector

	int numberOfPrincessSpawnPoints = 6;//there's only 6 points she can spawn within the cell
	Princess* princess;//the princess object found within the map
	std::vector<glm::vec2> princessPositions;//One of four initial starting points within the cell

public:
	void Initialise(MapObject* map,const char* filename);//by inputing a vector of strings and a size for each cell, spit out a maze
	void Draw();
	~NodeMap();

	void ClearNodeMap();//empties the nodemap of all nodes
	Node* GetNode(int x, int y) { return m_nodes[x + m_width * y]; }//return the node* at a given x, y co-ordinate
	Node* GetClosestNode(glm::vec2 worldPos);//find the closest node to a given x,y point

	void SetLever(Lever* l) { lever = l; }//sets the nodemaps lever to the lever object in main
	Lever* GetLever() { return lever; }//return the lever object
	glm::vec2 GetLeverPosition() { return leverPosition; }//retrives the only place the lever can spawn

	
	static std::vector<Node*> DijkstrasSearch(Node*& startNode, Node*& endNode);//By inputing a start and end node, use dijkstras search algorithm to find the shortest path
	std::vector<glm::vec2> GetGemPositions() { return gemPositions; }//obtain the list of supported gem spawn points
	int GetNumberofGemPositions() { return numberOfGemPositions; }//obtain the number of okayd gem posiitons

	void SetPrincess(Princess* p) { princess = p; }//sets the princess created in main to the nodemaps princess
	Princess* GetPrincess() { return princess; }//returns the princess object
	int GetAmountOfPrincessSpawnPoints() { return numberOfPrincessSpawnPoints; }//returns the actual number of spawn points the princess can spawn
	std::vector<glm::vec2> GetPrincessPositions() { return princessPositions; }//returns the actual spawn points the princess can spawn
	
	
};