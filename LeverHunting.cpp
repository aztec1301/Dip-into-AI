#include "LeverHunting.h"
#include "agent.h"


void LeverHunting::Enter(Agent* target)
{
	if (target->GetPath().empty())//if no current path
	{
		Node* start = target->GetNodeMap().GetClosestNode(target->GetPosition());
		Node* end = target->GetNodeMap().GetClosestNode(target->GetNodeMap().GetLeverPosition());
		std::vector<Node*> path = target->GetNodeMap().DijkstrasSearch(start, end);
		target->GoToNode(start, end);
	}
	
}

void LeverHunting::Update(Agent* target, float deltaTime)
{
	int leeway = 1;
	//using vec2's was playing with a lot of flaots, and tiny numbers would add up quick, throwing off some of ther traversal of the agent
	//this leeway number allowed for some extra tiny moevement of the agent on the screen, and still allow the agent to work out it's pathing

	glm::vec2 velocity = target->GetPath()[target->GetCurrentIndex()]->position - target->GetPosition();//the velocity of the agent to the node it's moving towards
	glm::vec2 unitVector = target->UnitVector(velocity);//find the unit vector of the velocity

	int xDistance = velocity.x;
	if (xDistance < 0)//if we're moving left on screen
	{
		xDistance = -xDistance;//make our distance a positive number
	}
	int yDistance = velocity.y;
	if (yDistance < 0)//ifwe're moving up on screen
	{
		yDistance = -yDistance; //make ourt distance a positive number
	}

	if (xDistance < leeway) // if distance in the x direction is less than leeway (generally means we're not moving to  the left or right)
	{
		yDistance = yDistance - (target->GetSpeed() * deltaTime);//subtract our speed * delta time from our distance on the y axis
	}
	else if (yDistance < leeway)// if distance in the y direction is less than leeway (generally means we're not moving up or down)
	{
		xDistance = xDistance - (target->GetSpeed() * deltaTime);//subtract our speed * delta time from our distance on the x axis
	}
	if (xDistance > 0 || yDistance > 0)//if there is still distance between the agent and the node it's moving towards, move it towards the node
	{
		float newXPos = target->GetPosition().x + (target->GetSpeed() * deltaTime * unitVector.x);
		target->SetPositionX(newXPos);
		float newYPos = target->GetPosition().y + (target->GetSpeed() * deltaTime * unitVector.y);
		target->SetPositionY(newYPos);
	}
	else //we've either arrived or overshot it
	{
		int newIndex = target->GetCurrentIndex() + 1;
		target->SetCurrentIndex(newIndex);//go to the next node in the list
		if (target->GetCurrentIndex() == target->GetPath().size())//if we've reached the last node in the list
		{
			glm::vec2 newPosition = target->GetPath().back()->position;
			target->SetWholePosition(newPosition);//snap our agents position to the position of the node at the end of the path
			target->ClearPath();//clear the path, we finally made it to mount doom
		}
		else//there's more node's in the list
		{
			velocity = target->GetPath()[target->GetCurrentIndex()]->position - target->GetPosition(); //reset velocity to the new node from the agent
			unitVector = target->UnitVector(velocity);//find the unit vector of that velocity
			float newPos = target->GetPosition().x + xDistance;//start moving towards that new node
			target->SetPositionX(newPos);
			newPos = target->GetPosition().y + yDistance;
			target->SetPositionY(newPos);
		}
	}

	//Checking for collisions with lever
	//--------------------------------------------
	
	bool collision = false;
	if (target->GetPosition().x - target->GetNodeMap().GetLeverPosition().x == 0 &&
		target->GetPosition().y - target->GetNodeMap().GetLeverPosition().y == 0)//if we've touched the lever
	{
		target->GetNodeMap().GetLever()->FlipLever();//flip the lever
	}
	
	//-------------------------------------------
}
