#include "AnimationTask.h"
#include <iostream>
#define M_PI 3.14159265358979323846f  /* pipiska */

AnimationTask::~AnimationTask() {
	delete animation;
	target = nullptr;
}

AnimationTask::AnimationTask(Animation* animation, float* target) {
	this->animation = animation;
	this->target = target;
	this->counter = 0;
	this->timer = 0;
}

AnimationTask::AnimationTask(Animation* animation, float* target, unsigned int counter, float timer) {
	this->animation = animation;
	this->target = target;
	this->counter = counter;
	this->timer = timer;
}

float AnimationTask::calculatePosition(
	float startPosition, 
	float endPosition, 
	float startTime, 
	float endTime, 
	float currentTime
) {
	return startPosition + (endPosition - startPosition) * ((currentTime - startTime) / (endTime - startTime));
}

float AnimationTask::calculatePosition(
	float startPosition, 
	float endPosition, 
	float startTime, 
	float endTime, 
	float currentTime, 
	float limit
) {
	if (float(endPosition - startPosition) < float(-limit / 2)) {	
		startPosition -= limit;
	}
	else if (float(endPosition - startPosition) > float(limit / 2)) {
		endPosition -= limit;
	}
	return startPosition + (endPosition - startPosition) * ((currentTime - startTime) / (endTime - startTime));
}

void AnimationTask::animateLoop(float& frameTime) {
	timer += frameTime;
	while (timer > animation->timeKeys[counter]) {
		counter += 1;
		if (counter == animation->keyCount) {
			timer -= animation->timeKeys[counter - 1];
			counter = 0;
		}
	}
	if (counter) {
		*target = calculatePosition(
			animation->stateKeys[counter - 1],
			animation->stateKeys[counter],
			animation->timeKeys[counter - 1],
			animation->timeKeys[counter],
			timer
		);
	}
	else {
		*target = calculatePosition(
			animation->stateKeys[(counter + animation->keyCount - 1) % animation->keyCount],
			animation->stateKeys[counter],
			0.f,
			animation->timeKeys[counter],
			timer
		);
	}
}

bool AnimationTask::animate(float& frameTime) {
	timer += frameTime;
	while (timer > animation->timeKeys[counter + 1]) {
		counter ++;
		if (counter == animation->keyCount - 1) {
			*target = animation->stateKeys[animation->keyCount - 1];
			return true; //finished
		}
	}
	*target = calculatePosition(
		animation->stateKeys[counter],
		animation->stateKeys[counter + 1],
		animation->timeKeys[counter],
		animation->timeKeys[counter + 1],
		timer
	);

	return false; //broken
}