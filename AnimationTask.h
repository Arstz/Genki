#pragma once
#include "Animation.h"

class AnimationTask {
	Animation animation;
	unsigned int counter;
	float timer;
	float* target;

	float calculatePosition(
		float startPosition,
		float endPosition,
		float startTime,
		float endTime,
		float currentTime
	);

	float calculatePosition(
		float startPosition,
		float endPosition,
		float startTime,
		float endTime,
		float currentTime,
		float limit
	);

public:
	AnimationTask();

	AnimationTask(const Animation& animation, float* target);

	void animateLoop(float& frameTime);
	bool animate(float& frameTime);
};