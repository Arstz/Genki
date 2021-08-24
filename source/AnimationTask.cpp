#include "AnimationTask.h"
#include <iostream>

#include "crtdbg.h"
#include "..\include\CRTDBG\mydbgnew.h"
#ifdef _DEBUG
#define new MYDEBUG_NEW
#endif

#define M_PI 3.14159265358979323846f  /* pipiska */

AnimationTask::AnimationTask() {
	this->targets = nullptr;
	this->counter = 0;
	this->timer = 0;
	this->targetCount = 0;
}

AnimationTask::~AnimationTask() {
	delete[] targets;
	targets = nullptr;
}

AnimationTask::AnimationTask(const AnimationTask& animationTask)
{
	this->animation = animationTask.animation;
	this->targets = new float* [animationTask.targetCount];
	for (unsigned int i = 0; i < animationTask.targetCount; i++) {
		this->targets[i] = animationTask.targets[i];
	}
	this->counter = 0;
	this->timer = 0;
	this->targetCount = animationTask.targetCount;
}

AnimationTask& AnimationTask::operator=(const AnimationTask& animationTask)
{
	delete[] targets;
	targets = nullptr;

	this->animation = animationTask.animation;
	this->targets = new float* [animationTask.targetCount];
	for (unsigned int i = 0; i < animationTask.targetCount; i++) {
		this->targets[i] = animationTask.targets[i];
	}
	this->counter = 0;
	this->timer = 0;
	this->targetCount = animationTask.targetCount;

	return *this;
}

AnimationTask::AnimationTask(const Animation& animation, float* target) {
	this->animation = animation;
	this->targets = new float*[] { target };
	this->counter = 0;
	this->timer = 0;
	this->targetCount = 1;
}

AnimationTask::AnimationTask(
	const Animation& animation,
	float** targets,
	unsigned int targetCount
) {
	this->animation = animation;
	this->targets = new float*[targetCount];
	for (unsigned int i = 0; i < targetCount; i++) {
		this->targets[i] = targets[i];
	}
	this->counter = 0;
	this->timer = 0;
	this->targetCount = targetCount;
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


/*void AnimationTask::animateLoop(float& frameTime) {
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
*/ 
//potom peredelaem

bool AnimationTask::animate(float frameTime) {
	timer += frameTime;
	while (timer > animation.getTimeKeysPointer()[counter + 1]) {
		counter ++;
		if (counter == animation.getKeyCount() - 1) {
			float value = animation.getStateKeysPointer()[animation.getKeyCount() - 1];
			for (unsigned int i = 0; i < targetCount; i++) {
				*targets[i] = value;
			}
			return true; //finished
		}
	}
	float value = calculatePosition(
		animation.getStateKeysPointer()[counter],
		animation.getStateKeysPointer()[counter + 1],
		animation.getTimeKeysPointer()[counter],
		animation.getTimeKeysPointer()[counter + 1],
		timer
	);
	for (unsigned int i = 0; i < targetCount; i++) {
		*targets[i] = value;
	}

	return false;
}

