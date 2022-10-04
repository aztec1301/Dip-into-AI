#pragma once
#include "Conditions.h"
#include "agent.h"

class LeverFlicked : public Condition
{
private:
	bool activated = true;//has the lever been activated?
public:

	LeverFlicked(bool isNotFlicked) : activated{ isNotFlicked } {}//sets lever to de-activated by default
	~LeverFlicked() {}

	bool IsTrue(Agent* agent);//checks to see if lever has been flicked

};