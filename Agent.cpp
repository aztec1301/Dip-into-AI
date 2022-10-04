#include "agent.h"
#include "AorQDecision.h"

void Agent::Update(float deltaTime)//will call update on our finite state machine, and let the machine tell us what to do, or, if no finite state machine and is an enemy, a decision tree
{
	if (!fsm)//if no finite state machine
	{
		rootDecision->MakeDecision(this, deltaTime);
	}
	else//there's a finite state machine
	{
		fsm->Update(this, deltaTime);
	}
	
}

void Agent::SetPositionX(float newPos)
{
	m_position.x = newPos;
}

void Agent::SetPositionY(float newPos)
{
	m_position.y = newPos;
}

void Agent::SetWholePosition(glm::vec2 newPosition)
{
	m_position = newPosition;
}

void Agent::SetCurrentIndex(int newIndex)
{
	m_currentIndex = newIndex;
}

void Agent::SetGemNumber(int stones)
{
	stonesInMap = stones;
}

void Agent::SetGemInfo(Gemstones* gemstones)
{
	gemstoneinfo = gemstones;
}

void Agent::SetBehavior(FiniteStateMachine* fsmNew)
{
	fsm = fsmNew;
	behaviour = fsmNew->GetCurrentState()->GetBehaviour();
}

void Agent::SetNodeMap(NodeMap& nodeMap)
{
	map = nodeMap;
}

void Agent::Draw()
{
	animation->Draw(Vector2{ m_position.x, m_position.y }, 0);
}

void Agent::GoToNode(Node* start, Node* end)
{

	m_path = NodeMap::DijkstrasSearch(start, end);//the main program gives us the start and end node, then the agent uses Djikstras to find the shortest way there
	m_currentIndex = 0;//sets the agents current position to 0 in the path vector
}

void Agent::SetNode(Node* start)
{
	m_currentNode = start;
	m_position = start->position;//set the agents position to the start node's position
}

glm::vec2 Agent::UnitVector(glm::vec2 direction)
{
	int magnitude = sqrt(((direction.x) * (direction.x)) + ((direction.y) * (direction.y)));//magnitude = sqrt(x^2 + y^2)
	glm::vec2 unitVector;//make a unit vector
	unitVector.x = direction.x / magnitude; //assign the values to the new vector 
	unitVector.y = direction.y / magnitude;
	return unitVector;//return unit vector
}

bool Agent::GemCheck(Gemstones gem)//used to see if we've collided with a gem
{
	if (m_position.x - gem.GetPosition().x == 0 && m_position.y - gem.GetPosition().y == 0) //if our position - gems position == 0
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Agent::TerrainCheck(NodeMap& nodeMap, int standardSpeed)
{
	Node* currentNode = nodeMap.GetClosestNode(GetPosition());//check wwhat node we're currently standing on

	if (currentNode->tileType == "bridge")//if bridge
	{
		SetSpeed((float)standardSpeed / 2);//half speed
	}

	else if (currentNode->tileType == "warp")//if warpgate
	{
		m_position = m_path[m_currentIndex + 1]->position;//take our position to the next node
		m_path[m_currentIndex] = m_path[m_currentIndex + 1];//move our path to the next node
	}
	else if (currentNode->tileType == "water")//if water
	{
		SetSpeed((float)standardSpeed / 4);//quarter speed
	}
	else if (currentNode->tileType == "magma")//if magma
	{
		SetSpeed((float)standardSpeed / 4);//quarter speed
	}
	else if (currentNode == nullptr)//if somethings gone horribly wrong
	{
		SetSpeed((float)standardSpeed * 4);//hopefully blitz out of there
	}
	else//dirt or any other standard
	{
		SetSpeed((float)standardSpeed);//normal speed
	}

}

void Agent::FindNextGem(int numberOfStones, NodeMap& nodeMap, Gemstones* gemstones)//find the gem closest to us (with regards to gscore) at point of call
{
	std::vector<Gemstones> gemScores;

	for (int i = 0; i < numberOfStones; ++i)
	{
		if (gemstones[i].IsCollected() == true)
		{
			continue;
		}
		Node* start = nodeMap.GetClosestNode(GetPosition());
		Node* end = nodeMap.GetClosestNode(gemstones[i].GetPosition());
		std::vector<Node*> path = nodeMap.DijkstrasSearch(start, end);
		gemstones[i].SetGScoreDistance(path.back()->gScore);
		gemScores.push_back(gemstones[i]);
	}

	if (!gemScores.empty())
	{
		Gemstones closest = gemScores[0];
		for (int i = 0; i < gemScores.size(); ++i)
		{
			if (gemScores[i].GetScoreDistance() < closest.GetScoreDistance())
			{
				closest = gemScores[i];
			}
		}


		Node* start = nodeMap.GetClosestNode(GetPosition());
		Node* end = nodeMap.GetClosestNode(closest.GetPosition());
		GoToNode(start, end);
	}
}

Agent::~Agent()
{
}
