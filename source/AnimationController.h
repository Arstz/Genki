#pragma once
#include <list>
#include "AnimationTask.h"

class AnimationController {
	static std::list<AnimationTask> animationTasks;
	static float* frameTime;
public:
	static void destroy();
	static void setTimePointer(float* frameTime);
	static void update();
	static void add(AnimationTask task);
};

