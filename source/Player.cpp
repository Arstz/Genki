#include "Player.h"

#include "crtdbg.h"
#include "..\include\CRTDBG\mydbgnew.h"
#ifdef _DEBUG
#define new MYDEBUG_NEW
#endif

void Player::move(float dx, float dy) {
	if (positionX && positionY) {
		*positionX += dx * 0.01;
		*positionY += dy * 0.01;
	}
}

void Player::setTarget(float* positionX, float* positionY) {
	this->positionX = positionX;
	this->positionY = positionY;
}
