#pragma once
#include <vector>

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
	Animation(char* byteArray, unsigned int& offset);

	float* getTimeKeysPointer();
	float* getStateKeysPointer();

	std::vector<char> getByteArray();

	unsigned int getKeyCount() const;
};

