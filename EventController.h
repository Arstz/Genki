#pragma once
#include "LevelEvent.h"
#include <SFML/Graphics.hpp>
#include <list>

class EventController
{
private:
	LevelEvent* level;
	
	int eventCount;
	int currentEvent;
	float* currentTime;

public:

	void startEvent(LevelEvent &levelEvent);

	void updateEvents();
	void updateActiveEventList();

	EventController();

	EventController(float& currentTime);
};

