#pragma once
#include "Conditions.h"
#include "agent.h"

class GemsCollected : public Condition
{
private:
	bool collected = true;//have all the gems been collected?
public:
	
	GemsCollected(bool isNotCollected) : collected{ isNotCollected } {}//sets to false by default
	~GemsCollected() {}

	bool IsTrue(Agent* agent);//checks to see if all gems have been collected in the map by looking at there collected bool
	
};