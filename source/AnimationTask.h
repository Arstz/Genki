#pragma once
#include "Animation.h"

class AnimationTask {
	Animation animation;
	unsigned int counter;
	unsigned int targetCount;
	float timer;
	float** targets;

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
	AnimationTask(const AnimationTask& animationTask);
	AnimationTask& operator=(const AnimationTask& animationTask);

	AnimationTask(const Animation& animation, float* target);

	AnimationTask(const Animation& animation, float** targets, unsigned int targetCount);

	//void animateLoop(float& frameTime);
	bool animate(float frameTime);
};