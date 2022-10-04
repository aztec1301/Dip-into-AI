#include "Gemstones.h"

void Gemstones::Draw()
{
	animation->Draw(Vector2{ position.x, position.y }, 0);
}

void Gemstones::SetPosition(glm::vec2 node)
{
	position.x = node.x;
	position.y = node.y;
}

void Gemstones::CollectGem()
{ 
	collected = true;
}
