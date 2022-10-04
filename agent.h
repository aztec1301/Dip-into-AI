#pragma once
#include "glm/glm.hpp"
#include <raylib.h>
#include <vector>
#include "Gemstones.h"
#include "Animation.h"
#include "FSM.h"

class Behaviour;
class Decision;


class Agent //an AI agent that can traverse the map
{
private:

	glm::vec2 m_position;//x,y position in the map
	std::vector<Node*> m_path; // the path our agent must take to reach the goal
	int m_currentIndex;//what number in the path vector we're up to
	int stonesInMap;//How many stones the agent needs to find
	float m_speed;//how fast we traverse the path
	int hp;//hp remaining 
	int stoneToGuard;//used for enemy agents to know hat stone to guard
	bool isEnemy = false;//flag to tell if agent is enemy
	bool deathAnimationOn = false;

	Node* m_currentNode;//the node we're currently at within the path vector
	Behaviour* behaviour;//the behaviour the agent is exhibiting at any given moment, controlled by the fsm
	Gemstones* gemstoneinfo;//information on every gemstone in scene
	Animation* animation;//sprite data
	FiniteStateMachine* fsm;//the state machine that will govern the agents actions
	NodeMap map;//the actual nodemap created in main (uses the nodemap&)
	Decision* rootDecision;//decision tree root, to be used only without prescence of fsm

public:
	void Update(float deltaTime);//the bulk of the agent's programming, working out how to move from A to B along the path
	void SetBehavior(FiniteStateMachine* fsm);//attaches a state machine to the agent and sets default behaviour
	Behaviour* GetBehaviour() { return behaviour; }//returns agents current behaviour
	void SetRootDecision(Decision* d) { rootDecision = d; }//sets the root decision for use in Decision trees
	void SetAnimation(Animation* a) { animation = a; }//sets the agents animation* with sprite data
	Animation* GetAnimation() { return animation; }//return the animation information
	void SetDeathAnimation() { deathAnimationOn = true; }//tells the program that the death animation has been loaded in
	bool GetDeathAnimation() { return deathAnimationOn; }//checks to see if the death animation has been loaded

	std::vector<Node*> GetPath() { return m_path; }//return the path the agent is following
	void ClearPath() { m_path.clear(); }//clear the path the agent is on
	void GoToNode(Node* start, Node* end);//a function the main program can tell the agent to do, giving it a start and end point, so the agent can work out the shortest path
	void SetNode(Node* start);//set a start point for the agent, usually it's current position
	void SetNodeMap(NodeMap& map);//give the agent the adress of the nodemap created in main
	NodeMap& GetNodeMap() { return map; }//returns the adress of the nodemap

	void FindNextGem(int numberOfStones, NodeMap& nodeMap, Gemstones* gemstones);//finds the next closest gem to the agent
	void SetGemNumber(int stones);//gets the amount of gems in map
	void SetGemInfo(Gemstones* gemstones);//assigns the agent with a gemstone array
	bool GemCheck(Gemstones gem);//lets us know if we've collided with a  gem
	int GetGemNumber() { return stonesInMap; }//returns the amount of stones in the map
	Gemstones* GetGemInfo() { return gemstoneinfo; }//returns the gemstone array
	void SetGemToGuard(int gemNumber) { stoneToGuard = gemNumber; }//tells the agent what stone it needs to guard
	int GetGemToGuard() { return stoneToGuard; }//returns what stone the agent is guarding
	
	void SetSpeed(float speed) { m_speed = speed; }//set the speed of the agent
	float GetSpeed() { return m_speed; }//retirves m_speed
	void SetHP(int hitpoints) { hp = hitpoints; }//sets the hp of the agent
	int GetHP() { return hp; }//return the current hp of the agent
	void SetEnemy() { isEnemy = true; }//flags this agent as an enemy
	bool IsEnemy() { return isEnemy; }//check iff agent is enemy or not

	int GetCurrentIndex() { return m_currentIndex; }//retrieves m_currentIndex
	void SetCurrentIndex(int newIndex);//set the current index to a new int

	void TerrainCheck(NodeMap& nodeMap, int standardSpeed);//terrain check to set speed accordingly
	
	glm::vec2 GetPosition() { return m_position; }//return agents current position
	void SetPositionX(float newPos);//change the x value of position
	void SetPositionY(float newPos);//change the y value of position
	void SetWholePosition(glm::vec2 newPosition);//change the whole position

	glm::vec2 UnitVector(glm::vec2 direction);//work out the unit vector of a given nodes x,y position relative to the agents position
	
	Agent(Animation* a) : animation{ a } {}//builds an agent with given animation
	~Agent();
	void Draw();
};