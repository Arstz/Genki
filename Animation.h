#pragma once
class Animation
{
public:
	unsigned int keyCount;
	float* timeKeys;
	float* stateKeys;

	Animation(unsigned int keyCount, float* timeKeys, float* stateKeys)
	{
		this->keyCount = keyCount;
		this->timeKeys = timeKeys;
		this->stateKeys = stateKeys;
	}
	Animation()	{}
};

