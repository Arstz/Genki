#pragma once
#include "LevelEvent.h"
#include <list>

class EventController
{
private:
	LevelEvent* level;
	std::list<LevelEvent> activeEvents;
	int eventCount;
	int currentEvent;
	float* currentTime;
public:
	void updateEvents();
	void updateActiveEventList();

	EventController();

	EventController(float& currentTime);
};

