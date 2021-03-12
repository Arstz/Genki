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

	void updateEvents();
	void updateActiveEventList();

	EventController();

	EventController(float* currentTime, int eventCount, LevelEvent* level);
};

