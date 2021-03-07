#pragma once
class Animation
{
public:
	short unsigned int keyCount;
	float* timeKeys;
	float* stateKeys;

	Animation(short unsigned int keyCount, float* timeKeys, float* stateKeys)
	{
		this->keyCount = keyCount;
		this->timeKeys = timeKeys;
		this->stateKeys = stateKeys;
	}
	Animation()	{}
};

