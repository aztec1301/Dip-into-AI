#pragma once
#include "Conditions.h"
#include "agent.h"

class SeeOtherAgent : public Condition
{
private:
	bool LineOfSight = false; //Can the agent see the other agent (enemy or hero)
public:

	SeeOtherAgent(bool canSee) : LineOfSight{ canSee } {}//set Line of sight to false by default 
	SeeOtherAgent() {}

	bool IsTrue(Agent* agent);//checks to see if agent can see other agent

};