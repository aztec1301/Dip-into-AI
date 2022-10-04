#include "Lever.h"

void Lever::Draw()
{
	animation->Draw(Vector2{ position.x, position.y }, 0);
}

void Lever::SetPosition(glm::vec2 node)
{
	position.x = node.x;
	position.y = node.y;
}

void Lever::FlipLever()
{
	flipped = true;
}