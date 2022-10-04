#include "LeverFlicked.h"

bool LeverFlicked::IsTrue(Agent* agent) // returns true if the levers flicked state is set to true
{
	if (agent->GetNodeMap().GetLever()->IsFlipped() == true)
	{
		activated = true;
	}
	return activated;
}