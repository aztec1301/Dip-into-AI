#include "AtPost.h"

bool AtPost::IsTrue(Agent* agent)//returns true if agent is ontop of the gem it needs to be "guarding"
{
	if (agent->GetPosition() == agent->GetGemInfo()[agent->GetGemToGuard()].GetPosition())
	{
		atPost = true;
	}
	return atPost;
}