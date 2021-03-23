#pragma once
#include "Animation.h"

class AnimationTask
{
private:

	Animation* animation;
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
	~AnimationTask();

	AnimationTask(Animation* animation, float* target);
	AnimationTask(Animation* animation, float* target, unsigned int counter, float timer);

	void animateLoop(float& frameTime);
	bool animate(float& frameTime);
};