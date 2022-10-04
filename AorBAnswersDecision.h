#pragma once

#include "Decision.h"
#include "Agent.h"
#include "Conditions.h"

class QAorBAnswersDecision : public Decision//if the previous condition would result in one of two behaviours, this is the class called
{
private:
	Behaviour* behaviour1;//first possible behaviour
	Behaviour* behaviour2;//second possible behaviour
	Condition* condition;//condition that leads us to choosing one of two behaviours

public:

	void MakeDecision(Agent* enemy, float delatTime)//figure out what behaviour to choose
	{
		if (condition->IsTrue(enemy) == true)//if condition true
		{
			behaviour1->Update(enemy, delatTime);//load behaviour 1
		}
		else//if condition false
		{
			behaviour2->Update(enemy, delatTime);// load behaviour 2
		}
	}

	void SetBehaviour1(Behaviour* b) { behaviour1 = b; }//used to set the first behaviour
	void SetBehaviour2(Behaviour* b) { behaviour2 = b; }//used to set the second behaviour
	void SetCondition(Condition* c) { condition = c; }//used to set the condition of this decision
	
};
