#pragma once
#include "Behaviourr.h"

class Attack : public Behaviour
{
private:

public:

	void Update(Agent* target, float deltaTime) {}//update called every frame while active
	void Enter(Agent* target) {};//called only once when entering state
	void Exit(Agent* agent) {};//called only once when exiting state
};
