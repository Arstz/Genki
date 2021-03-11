#pragma once
#include "Animation.h"

class AnimationTask
{
private: 

	Animation* animation;
	short unsigned int counter;
	float timer;
	float* target;

	float calculatePosition(float startPosition, float endPosition, const float& startTime, const float& endTime, const float& currentTime);
	float calculatePosition(float startPosition, float endPosition, const float& startTime, const float& endTime, const float& currentTime, const float& limit);

public:
	AnimationTask(void)	{}

	AnimationTask(Animation& animation, float& target)
	{
		this->animation = &animation;
		this->target = &target;
		this->counter = 0;
		this->timer = 0;
	}

	AnimationTask(Animation& animation, float& target, short unsigned int counter, float timer)
	{
		this->animation = &animation;
		this->target = &target;
		this->counter = counter;
		this->timer = timer;
	}
	void animate(float& frameTime);
};