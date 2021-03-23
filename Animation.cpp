#pragma once
#include "Animation.h"

Animation::Animation() {}
Animation::Animation(unsigned int keyCount, float* timeKeys, float* stateKeys) {
	this->keyCount = keyCount;
	this->timeKeys = timeKeys;
	this->stateKeys = stateKeys;
}

Animation::~Animation() {
	delete[] timeKeys;
	delete[] stateKeys;
}