#include "IsDead.h"


bool IsDead::IsTrue(Agent* agent)//returns true if agent is dead
{
	if (agent->GetHP() <= 0)
	{
		died = true;
	}
	return died;
}
