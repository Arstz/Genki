#pragma once
#include "LevelEvent.h"

class BackgroundColorAnimationEvent : public LevelEvent {
	Animation animation;
	uint valueNum;

	BackgroundColorAnimationEvent(Animation animation, uint valueNum, float initTime);
public:
	static BackgroundColorAnimationEvent* create(
		Animation animation,
		uint valueNum,
		float initTime
	);
	static BackgroundColorAnimationEvent* create(
		char* byteArray,
		float initTime
	);
	void start() override;
	std::vector<char> getByteArray() override;
};