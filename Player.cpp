#include "Player.h"

void Player::move(float dx, float dy) {
	for (int i = 0; i < shape->vertexCount * 2; i += 2) {
		shape->vertexCoords[i] += dx * 0.01;
		shape->vertexCoords[i+1] += dy * 0.01;
		std::cout << shape->vertexCount;
	}
}

void Player::bind(Shape* shape) {
	this->shape = shape;
}
