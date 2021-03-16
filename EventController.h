#pragma once
#include "LevelEvent.h"
#include <list>
#include <vector>

class EventController
{
public:
	static std::vector<LevelEvent*> level;
	static int currentEvent;
	static float* currentTime;

	static void updateEvents();
	static void updateActiveEventList();
};