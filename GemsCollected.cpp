#include "GemsCollected.h"


bool GemsCollected::IsTrue(Agent* agent)//returns true if all gems collected
{
	int gemsCollected = 0;
	for (int i = 0; i < agent->GetGemNumber(); ++i)
	{
		if (agent->GetGemInfo()[i].IsCollected() == false)
		{
			collected = false;
		}
		if (agent->GetGemInfo()[i].IsCollected() == true)
		{
			gemsCollected++;
		}
	} 
	if (gemsCollected == agent->GetGemNumber())
	{
		collected = true;
	}
	return collected;
}
