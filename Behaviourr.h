#pragma once
class Agent;

class Behaviour //abstract class, all behaviours need to have the following function
{
public:
	virtual void Update(Agent* agent, float deltaTime) = 0;//update function to be overwritten by each behaviour
	virtual void Enter(Agent* agent) {};//function called on entry of a behaviour (overwritten by each behaviour)
	virtual void Exit(Agent* agent) {};//function called on exit of a behaviour (overwritten by each behaviour)
};