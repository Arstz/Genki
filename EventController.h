#pragma once
#include "LevelEvent.h"
#include <list>
#include <vector>

class EventController
{
private:
	std::vector<LevelEvent*> level;
	
	int eventCount;
	int currentEvent;
	float* currentTime;

public:

	void updateEvents();
	void updateActiveEventList();

	EventController();

	EventController(float* currentTime, int eventCount, std::vector<LevelEvent*> level);
};