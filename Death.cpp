#include "Death.h"
#include "agent.h"

void Death::Enter(Agent* target)//called upon enetering behaviour from fsm
{
	if (target->IsEnemy() == true)//if the agent is an enemy agent
	{
		Animation* dead = new Animation(Rectangle{ 0, 0, 16, 16 }, "EnemyDeath.txt");//set their animation to the enemy death.txt animation
		target->SetAnimation(dead);
	}
	if (target->IsEnemy() == false)//if the agent is the hero
	{
		Animation* dead = new Animation( Rectangle{0, 0, 16, 16}, "HeroDeath.txt");//set their animation to the heroDeath.txt
		target->SetAnimation(dead);
	}
}
void Death::Update(Agent* target, float deltaTime)
{
	if (target->IsEnemy() == false)//if target is hero
	{
		float fps = target->GetAnimation()->GetFPS();//this is all checking to see if the little spin od death animation has played from the enter state
		std::vector<Rectangle> frames = target->GetAnimation()->GetFrames();
		int i = (int)(GetTime() * fps) % frames.size();

		if (i == 3)//once it has
		{
			Animation* dead = new Animation(Rectangle{ 0, 0, 16, 16 }, "HeroDeathPermanent.txt");//the hero's animation will be set to permanently on the floor
			target->SetAnimation(dead);
		}
	}
	if (target->IsEnemy() == true)//ifd it's an enemy agent
	{
		if (target->GetDeathAnimation() == false)//if the death animation hasn't already been loaded once
		{
			Animation* dead = new Animation(Rectangle{ 0, 0, 16, 16 }, "EnemyDeathPermanent.txt");//load in the permanent death animation from the tcxt file
			target->SetAnimation(dead);
			target->SetDeathAnimation();
		}
		
	}
	
}