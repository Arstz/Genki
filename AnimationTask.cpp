#include "AnimationTask.h"
#include <iostream>

#include "crtdbg.h"
#include "mydbgnew.h"
#ifdef _DEBUG
#define new MYDEBUG_NEW
#endif

#define M_PI 3.14159265358979323846f  /* pipiska */

AnimationTask::AnimationTask() {
	this->target = nullptr;
	this->counter = 0;
	this->timer = 0;
}

AnimationTask::AnimationTask(const Animation& animation, float* target) {
	this->animation = animation;
	this->target = target;
	this->counter = 0;
	this->timer = 0;
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
	while (timer > animation.getTimeKeysPointer()[counter]) {
		counter += 1;
		if (counter == animation.getKeyCount()) {
			timer -= animation.getTimeKeysPointer()[counter - 1];
			counter = 0;
		}
	}
	if (counter) {
		*target = calculatePosition(
			animation.getStateKeysPointer()[counter - 1],
			animation.getStateKeysPointer()[counter],
			animation.getTimeKeysPointer()[counter - 1],
			animation.getTimeKeysPointer()[counter],
			timer
		);
	}
	else {
		*target = calculatePosition(
			animation.getStateKeysPointer()[(counter + animation.getKeyCount() - 1) % animation.getKeyCount()],
			animation.getStateKeysPointer()[counter],
			0.f,
			animation.getTimeKeysPointer()[counter],
			timer
		);
	}
}

bool AnimationTask::animate(float& frameTime) {
	timer += frameTime;
	while (timer > animation.getTimeKeysPointer()[counter + 1]) {
		counter ++;
		if (counter == animation.getKeyCount() - 1) {
			*target = animation.getStateKeysPointer()[animation.getKeyCount() - 1];
			return true; //finished
		}
	}
	*target = calculatePosition(
		animation.getStateKeysPointer()[counter],
		animation.getStateKeysPointer()[counter + 1],
		animation.getTimeKeysPointer()[counter],
		animation.getTimeKeysPointer()[counter + 1],
		timer
	);

	return false;
}

