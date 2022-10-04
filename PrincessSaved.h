#pragma once
#include "Conditions.h"
#include "agent.h"

class PrincessSaved : public Condition
{
private:
	bool saved = true;//has the princess been saved?
public:

	PrincessSaved(bool isNotSaved) : saved{ isNotSaved } {}//sets the princess being saved to false by default
	~PrincessSaved() {}

	bool IsTrue(Agent* agent);//checks to see if hero has reached princess

};