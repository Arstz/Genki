#pragma once

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

	float* getTimeKeysPointer();
	float* getStateKeysPointer();

	unsigned int getKeyCount() const;
};

