#include "NodeMap.h"
//#include <iostream>
#include "raylib.h"
#include <algorithm>

void NodeMap::Initialise(MapObject* map, const char* filename)
{
	m_height = map->y_height;
	m_width = map->x_width;
	m_cellSize = map->tilesize;//set the size of the map cells to a given size
	m_nodes = new Node * [m_width * m_height];

	std::ifstream filein(filename);//open an fstream on the filename
	std::string line;//line needed dependent on use

	for (int i = 0; i < 3; i++)
	{
		std::getline(filein, line);
	}
	std::istringstream is{ line };
	int numberOfTiles;
	is >> numberOfTiles;

	for (int i = 0; i < numberOfTiles + 1; ++i)
	{
		std::getline(filein, line);
		is.clear();
		is.str(line);
	}

	// loop over the strings, creating Node entries as we go
	for (int y = 0; y < m_height; y++)
	{
		for (int x = 0; x < m_width; x++)
		{
			
			bool noNode = false;
			float gScore;
			int numberIn;
			std::string type;
			filein >> numberIn;
			switch (numberIn)
			{
			case 2:
				gScore = 1; //Dirt
				type = "dirt";
				break;
			case 4:
				gScore = 2; // Bridges
				type = "bridge";
				break;
			case 5:
				gScore = 420; //Warp Gates (the 420 is later changed to 1)
				type = "warp";
				break;
			case 7:
				gScore = 100; //Water
				type = "water";
				break;
			case 8:
				gScore = 100; //Magma
				type = "magma";
				break;
			default:
				noNode = true;
				m_nodes[x + (m_width * y)] = nullptr;
				
				break;
			}
			
			if (noNode == false)
			{
				Node* node = new Node(((float)x + 0.5f) * m_cellSize, ((float)y + 0.5f) * m_cellSize, gScore);
				node->tileType = type;
				m_nodes[x + (m_width * y)] = node;
			}
		}

	} 
	

	filein.close();

	//now loop over the nodes, creating connections between each node and it's
	//neighbour to the West and South on the grid. This will link up all the nodes

	for (int y = 0; y < m_height; y++)
	{
		for (int x = 0; x < m_width; x++)
		{
			Node* node = GetNode(x, y);
			if (node)
			{
				//see if there's a node to our west, checking for array overruns
				//first if we're on the west-most edge
				Node* nodeWest = x == 0 ? nullptr : GetNode(x - 1, y);
				if (nodeWest)
				{
					node->ConnectTo(nodeWest, nodeWest->gScore); //TODO weights
					nodeWest->ConnectTo(node, node->gScore);
				}

				//see if there's a node south of us, check,ing for array index
				//overruns again

				Node* nodeSouth = y == 0 ? nullptr : GetNode(x, y - 1);
				if (nodeSouth)
				{
					node->ConnectTo(nodeSouth, nodeSouth->gScore);
					nodeSouth->ConnectTo(node, node->gScore);
				}
			}
			//creates a strange portal if tiles are warp gates
			if (node != nullptr && node->gScore == 420)
			{
				node->gScore = 1;
				Node* otherPortal = x == 0 ? nullptr : GetNode(x + 8, y);
				otherPortal->gScore = 1;
				node->ConnectTo(otherPortal, node->gScore);
				otherPortal->ConnectTo(node, otherPortal->gScore);
				
			}
		}
	}

	

	//Generate a list of okay positions that gems can spawn on
	
	for (int i = 0; i < numberOfGemPositions; i++)
	{
		glm::vec2 vector;
		gemPositions.push_back(vector);

		switch (i)
		{
		case 0:
			gemPositions[i].x = GetNode(22, 9)->position.x;
			gemPositions[i].y = GetNode(22, 9)->position.y;
			break;
		case 1:
			gemPositions[i].x = GetNode(22, 21)->position.x;
			gemPositions[i].y = GetNode(22, 21)->position.y;
			break;
		case 2:
			gemPositions[i].x = GetNode(32, 10)->position.x;
			gemPositions[i].y = GetNode(32, 10)->position.y;
			break;
		case 3:
			gemPositions[i].x = GetNode(32, 12)->position.x;
			gemPositions[i].y = GetNode(32, 12)->position.y;
			break;
		case 4:
			gemPositions[i].x = GetNode(45, 12)->position.x;
			gemPositions[i].y = GetNode(45, 12)->position.y;
			break;
		case 5:
			gemPositions[i].x = GetNode(10, 9)->position.x;
			gemPositions[i].y = GetNode(10, 9)->position.y;
			break;
		case 6:
			gemPositions[i].x = GetNode(10, 13)->position.x;
			gemPositions[i].y = GetNode(10, 13)->position.y;
			break;
		case 7:
			gemPositions[i].x = GetNode(6, 18)->position.x;
			gemPositions[i].y = GetNode(6, 18)->position.y;
			break;
		case 8:
			gemPositions[i].x = GetNode(14, 18)->position.x;
			gemPositions[i].y = GetNode(14, 18)->position.y;
			break;
		case 9:
			gemPositions[i].x = GetNode(42, 25)->position.x;
			gemPositions[i].y = GetNode(42, 25)->position.y;
			break;
		}
	}
	
	//This is the only position the only lever in the simulation will spawn at. That's it. 

	leverPosition.x = GetNode(46,25)->position.x;
	leverPosition.y = GetNode(46, 25)->position.y;
	

	//Generate a list of okay positions that the princess can spawn on
	for (int i = 0; i < numberOfPrincessSpawnPoints; ++i)
	{
		glm::vec2 vector;
		princessPositions.push_back(vector);

		switch (i)
		{
		case 0:
			princessPositions[i].x = GetNode(35, 3)->position.x;
			princessPositions[i].y = GetNode(35, 3)->position.y;
			break;

		case 1:
			princessPositions[i].x = GetNode(36, 3)->position.x;
			princessPositions[i].y = GetNode(36, 3)->position.y;
			break;
		case 2:
			princessPositions[i].x = GetNode(37, 3)->position.x;
			princessPositions[i].y = GetNode(37, 3)->position.y;
			break;
		case 3:
			princessPositions[i].x = GetNode(35, 4)->position.x;
			princessPositions[i].y = GetNode(35, 4)->position.y;
			break;
		case 4:
			princessPositions[i].x = GetNode(36, 4)->position.x;
			princessPositions[i].y = GetNode(36, 4)->position.y;
			break;

		case 5:
			princessPositions[i].x = GetNode(37, 4)->position.x;
			princessPositions[i].y = GetNode(37, 4)->position.y;
			break;
		}
	}
}

void NodeMap::Draw()
{
	//Grey colour for the line
	Color lineColor;
	lineColor.a = 255;
	lineColor.r = 255;
	lineColor.g = 255;
	lineColor.b = 255;

	for (int y = 0; y < m_height; y++)
	{
		for (int x = 0; x < m_width; x++)
		{
			Node* node = GetNode(x, y);
			if (node == nullptr)
			{
				continue;
			}
			else
			{
				// draw the connections between the node and its neighbours
				for (int i = 0; i < node->connections.size(); i++)
				{
					Node* other = node->connections[i].target;
					DrawLine((x + 0.5f) * m_cellSize, (y + 0.5F) * m_cellSize,
						(int)other->position.x, (int)other->position.y,
						lineColor);
				}
			}
		}
	}
}

std::vector<Node*> NodeMap::DijkstrasSearch(Node*& startNode, Node*& endNode)
{
	
	if (startNode == endNode)//clicked on the agent
	{
		std::vector<Node*> emptyPath;
		return emptyPath;//return the fact that there's no path

	}
	//Initialise the starting path
	startNode->gScore = 0;
	startNode->previous = nullptr;

	//Create our temporary lists for storing the nodes we're visiting/visited
	std::vector<Node*> openList;
	std::vector<Node*> closedList;

	openList.push_back(startNode);//put the start node into the list of nodes to be worked through
	
	while (!openList.empty())//WHile there's nodes still to be worked through
	{
		//Make sure all nodes in the list are ordered from smallest traversal score to largest traversal score
		//---------------------------------------------------------------------------------------------
		
		bool swapped = true;
		while (swapped == true)
		{
			swapped = false;
			for (int i = 1; i < openList.size(); ++i)
			{
				if (openList[i - 1]->gScore > openList[i]->gScore)
				{
					Node* hotSwap = openList[i];
					openList[i] = openList[i - 1];
					openList[i - 1] = hotSwap;
					swapped = true;
				}
			}
		}
		//----------------------------------------------------------------------------------------------

		Node* currentNode = openList[0]; //set the first node in the open list to 'current node'

		// If we visit the endNode, then we can exit early.
		// Sorting the openList above guarantees the shortest path is found,
		// given no negative costs (a prerequisite of the algorithm).
		// This is an optional optimisation that improves performance,
		// but doesn’t always guarantee the shortest path.

		if (currentNode == endNode)//WE MADE IT BOYS!!!!!
		{
			break;
		}

		openList.erase(std::find(openList.begin(), openList.end(), currentNode));//Remove the current node from the process list 

		closedList.push_back(currentNode);//add it to the processed list

		int firstScore = currentNode->gScore;
		

		for (int i = 0; i < currentNode->connections.size(); i++)//for every node connected to the current node
		{
			
			bool inVector = (std::find(closedList.begin(), closedList.end(), currentNode->connections[i].target) != closedList.end());//See if the connection is already in closed list

			

			if (inVector == false)//if it wasn't
			{
				currentNode->gScore = firstScore + currentNode->connections[i].cost;//our current node's g-score increases by whatever connectiion we're at's cost

				// Have not yet visited the node.
				// So calculate the Score and update its parent.
				// Also add it to the openList for processing.
				// This will also sort out our node path, connecting those with the lowest g-scores together
				// until we have one path connecting the start and end points together, with the lowerst possible g-scores as the edges
				//-------------------------------------------------------------------------
				bool inList = false;
				for (int k = 0; k < openList.size(); k++)
				{
					if (currentNode->connections[i].target == openList[k])
					{
						inList = true;
					}
				}
				if (inList == false)
				{
					currentNode->connections[i].target->gScore = currentNode->gScore;
					currentNode->connections[i].target->previous = currentNode;
					openList.push_back(currentNode->connections[i].target);
				}
				else if (currentNode->gScore > currentNode->connections[i].target->gScore)
				{
					currentNode->connections[i].target->gScore = currentNode->gScore;
					currentNode->connections[i].target->previous = currentNode;
				}
				//---------------------------------------------------------------------------
				
			}
		}


	}
	std::vector<Node*> path;//Create a path
	Node* currentNode = endNode;//start at the end given to us

	while (currentNode != nullptr)//as long as we have nodes to go through
	{
		path.insert(path.begin(), currentNode);//put the currentnode into the path
		currentNode = currentNode->previous;//become it's previous node
	}

	return path;//return the shortest possible path



}



Node* NodeMap::GetClosestNode(glm::vec2 worldPos)//find the closest node to two given points
{
	int i = (int)(worldPos.x / m_cellSize);//find a node within this given area
	if (i < 0 || i >= m_width) return nullptr;//if there's none, return nullptr

	int j = (int)(worldPos.y / m_cellSize);//same here
	if (j < 0 || j >= m_width) return nullptr;

	return GetNode(i, j);//return the closest node
}

NodeMap::~NodeMap()
{
}

void NodeMap::ClearNodeMap()
{
	for (int i = 0; i < m_width * m_height; ++i)
	{
		delete m_nodes[i];
	}
	
}