#include "Player.h"

void Player::move(float dx, float dy) {
	shape->positionX += dx * 0.01;
	shape->positionY += dy * 0.01;
}

void Player::bind(Shape* shape) {
	this->shape = shape;
}
