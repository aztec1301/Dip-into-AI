#pragma once
#include "Behaviourr.h"

class GemHunt : public Behaviour
{
private:
	
public:
	
	void Update(Agent* target, float deltaTime);//update called every frame while active in state machine
	void Enter(Agent* agent) {};//called only once when entering state
	void Exit(Agent* agent) {};//called only once when exiting state
};
