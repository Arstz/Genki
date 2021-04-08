#pragma once
#include "LevelEvent.h"

class CameraAnimationEvent : public LevelEvent {
	Animation animation;
	uint valueNum;

	CameraAnimationEvent(
		Animation animation,
		uint valueNum,
		float initTime
	);

public:
	static CameraAnimationEvent* create(
		Animation animation,
		uint valueNum,
		float initTime
	);

	static CameraAnimationEvent* create(
		char* byteArray,
		float initTime
	);

	void start() override;
	std::vector<char> getByteArray() override;
};