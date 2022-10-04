#pragma once
#include "Behaviourr.h"

class LeverHunting : public Behaviour
{
public:
	void Update(Agent* target, float deltaTime); // update called every frame while active
	void Enter(Agent* agent);//called only once when entering state

};