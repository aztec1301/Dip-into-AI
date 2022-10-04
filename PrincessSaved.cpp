#include "PrincessSaved.h"


bool PrincessSaved::IsTrue(Agent* agent)//returns true if prioncess saved state is set to true
{
	if (agent->GetNodeMap().GetPrincess()->IsSaved() == true)
	{
		saved = true;
	}
	return saved;
}
