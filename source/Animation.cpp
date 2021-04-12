#pragma once
#include "Animation.h"

#include "crtdbg.h"
#include "..\include\CRTDBG\mydbgnew.h"
#ifdef _DEBUG
#define new MYDEBUG_NEW
#endif

Animation::Animation() {
	keyCount = 0;
	timeKeys = nullptr;
	stateKeys = nullptr;
}

Animation::Animation(const Animation& animation) {
	this->keyCount = animation.keyCount;

	this->timeKeys = new float[keyCount];
	this->stateKeys = new float[keyCount];

	for (int i = 0; i < keyCount; i++) {
		this->timeKeys[i] = animation.timeKeys[i];
		this->stateKeys[i] = animation.stateKeys[i];
	}
}

Animation::Animation(unsigned int keyCount, float* timeKeys, float* stateKeys) {
	this->keyCount = keyCount;

	this->timeKeys = new float[keyCount];
	this->stateKeys = new float[keyCount];

	for (int i = 0; i < keyCount; i++) {
		this->timeKeys[i] = timeKeys[i];
		this->stateKeys[i] = stateKeys[i];
	}
}

Animation::~Animation() {
	delete[] timeKeys;
	delete[] stateKeys;
	timeKeys = nullptr;
	stateKeys = nullptr;
}

Animation& Animation::operator=(const Animation& animation) {
	delete[] this->timeKeys;
	delete[] this->stateKeys;

	this->keyCount = animation.keyCount;

	this->timeKeys = new float[keyCount];
	this->stateKeys = new float[keyCount];

	for (int i = 0; i < keyCount; i++) {
		this->timeKeys[i] = animation.timeKeys[i];
		this->stateKeys[i] = animation.stateKeys[i];
	}
	return *this;
}

Animation::Animation(ByteArray* byteArray) {
	*byteArray >> keyCount;
	this->timeKeys = new float[keyCount];
	this->stateKeys = new float[keyCount];
	byteArray->read(timeKeys, sizeof(*timeKeys) * keyCount);
	byteArray->read(stateKeys, sizeof(*stateKeys) * keyCount);
}

float* Animation::getTimeKeysPointer() {
	return timeKeys;
}

float* Animation::getStateKeysPointer() {
	return stateKeys;
}

ByteArray Animation::getByteArray() {
	ByteArray byteArray(sizeof(keyCount) + (sizeof(*timeKeys) + sizeof(*stateKeys)) * keyCount);

	byteArray.add(keyCount);
	byteArray.add(timeKeys, sizeof(*timeKeys) * keyCount);
	byteArray.add(stateKeys, sizeof(*stateKeys) * keyCount);

	return byteArray;
}

unsigned int Animation::getKeyCount() const {
	return keyCount;
}

