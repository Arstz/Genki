#pragma once
#include <list>
#include "AnimationTask.h"

class AnimationController {
	static std::list<AnimationTask> animationTasks;
public:
	static void destroy();
	static void update(float frameTime);
	static void add(AnimationTask task);
};

