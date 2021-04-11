#pragma once
#include "ByteArray.h"

class Animation
{
	unsigned int keyCount;
	float* timeKeys;
	float* stateKeys;

public:
	Animation(unsigned int keyCount, float* timeKeys, float* stateKeys);
	Animation();
	Animation(const Animation &animation);
	~Animation();
	Animation& operator=(const Animation& animation);
	Animation(ByteArray* byteArray);

	float* getTimeKeysPointer();
	float* getStateKeysPointer();

	ByteArray getByteArray();

	unsigned int getKeyCount() const;
};


