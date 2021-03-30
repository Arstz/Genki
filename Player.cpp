#include "Player.h"

void Player::move(float dx, float dy) {
	*positionX += dx * 0.01;
	*positionY += dy * 0.01;
}

void Player::bind(Shape* shape) {
	this->shape = shape;
}

void Player::setTarget(float* positionX, float* positionY) {
	this->positionX = positionX;
	this->positionY = positionY;
}
