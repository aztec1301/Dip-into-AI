#pragma once

class Agent;//forward declare


class Condition//what is required for a transition to occur
{
public:
	virtual bool IsTrue(Agent* agent) = 0;//returns a bool, but this function is there to be overwritten
};