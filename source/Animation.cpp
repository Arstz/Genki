#pragma once
#include "Animation.h"
#include <string>

#include "crtdbg.h"
#include "..\include\CRTDBG\mydbgnew.h"
#ifdef _DEBUG
#define new MYDEBUG_NEW
#endif

Animation::Animation(const Animation& other) :
	keyCount	{other.keyCount},
	timeKeys	{new float[other.keyCount]},
	stateKeys	{new float[other.keyCount]}
{
	memcpy(timeKeys, other.timeKeys, keyCount * sizeof(*timeKeys));
	memcpy(stateKeys, other.stateKeys, keyCount * sizeof(*stateKeys));
}

Animation::Animation(
	unsigned int keyCount,
	float* timeKeys,
	float* stateKeys
) :
	keyCount	{keyCount},
	timeKeys	{new float[keyCount]},
	stateKeys	{new float[keyCount]}
{
	memcpy(this->timeKeys, timeKeys, keyCount * sizeof(*timeKeys));
	memcpy(this->stateKeys, stateKeys, keyCount * sizeof(*stateKeys));
}

Animation::~Animation() {
	delete[] timeKeys;
	delete[] stateKeys;
	timeKeys = nullptr;
	stateKeys = nullptr;
}

Animation& Animation::operator=(const Animation& other) {
	keyCount = other.keyCount;

	float* newTimeKeys = new float[keyCount];
	float* newStateKeys = new float[keyCount];

	memcpy(newTimeKeys, other.timeKeys, keyCount * sizeof(*timeKeys));
	memcpy(newStateKeys, other.stateKeys, keyCount * sizeof(*stateKeys));

	delete[] timeKeys;
	delete[] stateKeys;

	timeKeys	= newTimeKeys;
	stateKeys	= newStateKeys;

	newTimeKeys		= nullptr;
	newStateKeys	= nullptr;

	return *this;
}

Animation::Animation(ByteArray* byteArray) {
	*byteArray >> keyCount;
	timeKeys = new float[keyCount];
	stateKeys = new float[keyCount];
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

const float* Animation::getTimeKeysPointer() const {
	return timeKeys;
}

const float* Animation::getStateKeysPointer() const {
	return stateKeys;
}
