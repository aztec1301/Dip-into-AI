#pragma once
#include "Conditions.h"
#include "agent.h"

class IsDead : public Condition
{
private:
	bool died = false;//am dead maybe?
public:

	IsDead(bool dead) : died{ dead } {}//sets to no by default
	~IsDead() {}

	bool IsTrue(Agent* agent);//checks to see if agents hit points are =< 0

};
