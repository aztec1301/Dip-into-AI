#include "Princess.h"

void Princess::Draw()
{
	animation->Draw(Vector2{ position.x, position.y }, 0);
}

void Princess::SetPosition(glm::vec2 node)
{
	position.x = node.x;
	position.y = node.y;
}

void Princess::SavePrincess()
{
	saved = true;
}