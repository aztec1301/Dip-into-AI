#pragma once
#include "raylib.h"
#include"glm/glm.hpp"
#include "Animation.h"

class Princess
{
private:
	glm::vec2 position;//position on the map
	bool saved = false;//has the princess been saved default no
	int gScoreDistance;//used to see how close it is to the agent
	Animation* animation;//sprite information

public:
	Princess(Animation* a) { animation = a; }
	glm::vec2 GetPosition() { return position; }//return princess position on map
	void Draw();//draw the princess
	void SetPosition(glm::vec2 node);//set the original position of the princess
	void SavePrincess();//She's not actually in another castle!
	void SetGScoreDistance(int score) { gScoreDistance = score; }//set the score as to how far from the agent the lever is
	bool IsSaved() { return saved; }//what state is the princess in?
	int GetScoreDistance() { return gScoreDistance; }//return distance of how far from agent princess is with regards to gscore
	~Princess() {}
};
