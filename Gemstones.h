#pragma once
#include "raylib.h"
#include"glm/glm.hpp"
#include "NodeMap.h"
#include "Animation.h"


class Gemstones
{
private:
	glm::vec2 position;//position on the map
	bool collected = false;//has the gem been collected? default no
	int gScoreDistance;//used to see how close it is to the agent
	int numberOfSprites = 4;//Hardlock on this number
	Animation* animation;//sprite data

public:
	Gemstones() {}
	
	glm::vec2 GetPosition() { return position; }//return position of gemstone on the map
	void Draw();//draw a gem
	void SetPosition(glm::vec2 node);//set the map position of the gem
	void CollectGem();//obtain loot
	void SetAnimation(Animation* a) { animation = a; }//set the sprite of the gem
	int GetNumberOfSprites() { return numberOfSprites; }//returns the number of sprites
	bool IsCollected() { return collected; }//has the gem been collected?
	void SetGScoreDistance(int score) { gScoreDistance = score; }//set how far from the agent the gem is with regards to g score
	int GetScoreDistance() { return gScoreDistance; }//return distance from agent with regards to gscore

	~Gemstones() {}

	
};