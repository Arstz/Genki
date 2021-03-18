#include "Player.h"

void Player::move(float dx, float dy)
{
	for (int i = 0; i < shape->vertexCount * 2; i += 2) shape->vertexCoords[i] += dx*0.01;
	for (int i = 1; i < shape->vertexCount * 2; i += 2) shape->vertexCoords[i] += dy*0.01;
}
