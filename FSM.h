#pragma once
#include "Behaviourr.h"
#include "State.h"
#include "Conditions.h"

class FiniteStateMachine : public Behaviour//The state machine to look after....well...states
{
private:

	std::vector<State*> states;//a list of all states held by the state machine
	State* currentState;//the current state the machine is servicing
	
	

public:

	void AddState(State* state)//adds a state to the list of states in the machine
	{
		states.push_back(state);
	}

	FiniteStateMachine(State* currentState) : currentState{ currentState } 	//builds the FSM witha default state
	{
		
	}

	~FiniteStateMachine()//deletes all states in the machine
	{
		for (auto s : states)
		{
			delete s;
		}
	}

	virtual void Update(Agent* agent, float deltaTime)//this is the update function the agent will call when agent.update happens
	{
		State* newState = nullptr;//create an empty state container
		for (auto transitions : currentState->transitions)//for every transition the current state has
		{
			if (transitions.condition->IsTrue(agent))//see if the condition to activate that state is true
			{
				newState = transitions.targetState;//if any are, make the newstate container = the true state 
				break;//leave this search before we break it.
			}
		}

		if (newState)//if we did create a new state
		{
			currentState->ExitState(agent);//do whatever the agent needs to do to finish up in its current state by calling Exit
			currentState = newState;//assign the current state to the one we found to be true
			currentState->EnterState(agent);//let the agent do the welcome taks before getting into the main update of the state
		}
		

		currentState->Update(agent, deltaTime);//call update on the new state
	}


	State* GetCurrentState() { return currentState; }//will return the current state that the fsm is currently in
};
