#pragma once
#include <vector>
#include "Behaviourr.h"
#include "Conditions.h"

class State //Any given state that an agent can be in, controlled by the fsm
{
public:
	class Transition//a connection between states, allowing a state to see what state it can become, and more importantly, barring states from becoming other states
	{
	public:
		Condition* condition;//the condition that must take place for one transition to occur
		State* targetState;//the state this state will transition into
	};

private:
	Behaviour* behaviour;//the behaviour this state will follow
	
public:

	std::vector<Transition> transitions;//a list of transitions that this state can use

	State(Behaviour* b)//upon creation of a state, assign a behaviour so it knows what to do
	{
		behaviour = b;
	}
	~State();

	Behaviour* GetBehaviour() { return behaviour; }//returns the beahviour a state is using

	void AddTransition(Condition* condition, State* state)//adds a transition to the transitions list
	{
		transitions.push_back(Transition{condition, state});//a transition must have a condition and target state
	}


	virtual void EnterState(Agent* agent)//calls the behaviours entrance function, making the agent do things upon entry of this state
	{
		behaviour->Enter(agent);
	}
	virtual void ExitState(Agent* agent)//calls the behaviours exit function, making the agent do things upon exit of this state
	{
		behaviour->Exit(agent);
	}

	virtual void Update(Agent* agent, float deltaTime)//calls the behaviours update function, the main bulk of the state
	{
		behaviour->Update(agent, deltaTime);
	}
};