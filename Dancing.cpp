#include "Dancing.h"
#include "agent.h"

void Dancing::Enter(Agent* target)//called once the princess has been rescued
{
	
	Animation* dancing = new Animation(Rectangle{ 0, 0, 16, 16 }, "HeroDance.txt");//set the animation to the hero's dance text file
	target->SetAnimation(dancing);
}

