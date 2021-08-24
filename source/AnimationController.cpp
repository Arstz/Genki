#include "AnimationController.h"

#include "crtdbg.h"
#include "..\include\CRTDBG\mydbgnew.h"
#ifdef _DEBUG
#define new MYDEBUG_NEW
#endif

std::list<AnimationTask> AnimationController::animationTasks = std::list<AnimationTask>();

void AnimationController::destroy(){
	animationTasks.~list();
}

void AnimationController::update(float frameTime) {
	std::list<AnimationTask>::iterator i = animationTasks.begin();
	while (i != animationTasks.end()) {
		if (i->animate(frameTime)) {
			i = animationTasks.erase(i);
		}
		else i++;
	}
}
void AnimationController::add(AnimationTask task) {
	animationTasks.push_back(task);
}
