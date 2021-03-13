#include "EventController.h"
#include "LevelEvent.h"
#include <vector>
#include <iostream>

void EventController::updateActiveEventList() 
{
	while (currentEvent < eventCount && level[currentEvent]->getInitTime() < *currentTime) {
		std::cout << *currentTime<< "\n";
		level[currentEvent]->start();
		currentEvent++;
	}
}

EventController::EventController(){}
//                              ( ^ )

EventController::EventController(float* currentTime, int eventCount, std::vector<LevelEvent*> level)
{
	this->level = level;
	this->currentTime = currentTime;
	this->eventCount = eventCount;
	this->currentEvent = 0;
}

