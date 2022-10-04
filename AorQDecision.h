#pragma once

#include "Decision.h"
#include "agent.h"
#include "Conditions.h"



class AorQDecision : public Decision//if a decision may lead to more questions, this is the class called
{
private:
	Behaviour* behaviour;//resulting behaviour
	Decision* nextQuestion;//resulting question
	Condition* condition;//condition that decides if further questioning is necessary

public:

	void MakeDecision(Agent* enemy, float delatTime)
	{
		if (condition->IsTrue(enemy) == true)//if condition is true
		{
			behaviour->Update(enemy, delatTime);//follow behaviour
		}
		else//if condition is false
		{
			nextQuestion->MakeDecision(enemy, delatTime);//make the next set of questioning happen
		}
	}

	void SetBehaviour(Behaviour* b) { behaviour = b; }//set the behaviour
	void SetCondition(Condition* c) { condition = c; }//set the condition
	void SetNextQuestion(Decision* d) { nextQuestion = d; }//set next line of questioning
};