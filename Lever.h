#pragma once
#include "raylib.h"
#include"glm/glm.hpp"
#include "Animation.h"

class Lever
{
private:
	glm::vec2 position;//position on the map
	bool flipped = false;//has the lever been activated? default no
	int gScoreDistance;//used to see how close it is to the agent
	Animation* animation;//sprite 


public:
	Lever() {}
	glm::vec2 GetPosition() { return position; }//return lever position on map
	void Draw();//draw the lever
	void SetPosition(glm::vec2 node);//set the original position of the lever
	void SetAnimation(Animation* a) { animation = a; }
	void FlipLever();//PULL THE LEVER KRONK
	void SetGScoreDistance(int score) { gScoreDistance = score; }//set the score as to how far from the agent the lever is
	bool IsFlipped() { return flipped; }//what state is the lever in?
	int GetScoreDistance() { return gScoreDistance; }//return distance of how far from agent lever is with regards to gscore
	~Lever() {}
};