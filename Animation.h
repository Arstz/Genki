#pragma once
class Animation
{
public:
	unsigned int keyCount;
	float* timeKeys;
	float* stateKeys;

	Animation(unsigned int keyCount, float* timeKeys, float* stateKeys);
	Animation();
	~Animation();

};

