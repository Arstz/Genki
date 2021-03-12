#include "EventController.h"

void EventController::updateActiveEventList() 
{
	while (currentEvent < eventCount && level[currentEvent].getInitTime() < *currentTime) {
		currentEvent++;
	}
}

EventController::EventController(){}
//                              ( ^ )

EventController::EventController(float* currentTime, LevelEvent* level)
{
	this->level = level;
	this->currentTime = currentTime;
}

