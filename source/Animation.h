#pragma once
#include "ByteArray.h"

class Animation {
	unsigned int keyCount {0};
	float* timeKeys {nullptr};
	float* stateKeys {nullptr};

public:
	Animation() = default;
	Animation(
		unsigned int keyCount, 
		float* timeKeys, 
		float* stateKeys
	);

	Animation(const Animation& other);
	~Animation();
	Animation& operator=(const Animation& other);
	Animation(ByteArray* byteArray);

	float* getTimeKeysPointer();
	float* getStateKeysPointer();

	ByteArray getByteArray();

	unsigned int getKeyCount() const;

	const float* getTimeKeysPointer() const;
	const float* getStateKeysPointer() const;
};


