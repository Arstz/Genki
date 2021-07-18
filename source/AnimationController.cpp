#include "AnimationController.h"

#include "crtdbg.h"
#include "..\include\CRTDBG\mydbgnew.h"
#ifdef _DEBUG
#define new MYDEBUG_NEW
#endif

std::list<AnimationTask> AnimationController::animationTasks = std::list<AnimationTask>();
float* AnimationController::frameTime = nullptr;

void AnimationController::destroy(){
	animationTasks.~list();
}

void AnimationController::setTimePointer(float* frameTime) {
	AnimationController::frameTime = frameTime;
}

void AnimationController::update() {
	std::list<AnimationTask>::iterator i = animationTasks.begin();
	while (i != animationTasks.end()) {
		if (i->animate(*frameTime)) {
			i = animationTasks.erase(i);
		}
		else i++;
	}
}
void AnimationController::add(AnimationTask task) {
	animationTasks.push_back(task);
}
