#pragma once

#include "Conditions.h"
#include "agent.h"

class AtPost : public Condition
{
private:
	bool atPost = false;//is the enemy at the gem it needs to be guarding?
public:

	AtPost(bool posted) : atPost{ posted } {}//no by default
	AtPost() {}

	bool IsTrue(Agent* agent);//checks to see if enemy's position equals the gem it should be guardings position

};