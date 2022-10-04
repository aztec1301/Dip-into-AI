#pragma once
class Agent;

class Decision//abstract class for overriding
{
public:
	virtual void MakeDecision(Agent* enemy, float delatTime) = 0;//used to make decisions that wioll either result in behaviours or more questions

	virtual void SetCondition(Condition* c) {};//used to set the condition the decision will assess

	virtual void SetBehaviour(Behaviour* b) {};//used to set behaviours in A ro Q decisions
	virtual void SetNextQuestion(Decision* d) {};//set the next question in A or Q decisions

	virtual void SetBehaviour1(Behaviour* b) {};//set the first behaviour in A or B decisions
	virtual void SetBehaviour2(Behaviour* b) {};//set the second behaviour in A or B decisions
};
