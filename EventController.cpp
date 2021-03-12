#include "EventController.h"
#include "LevelEvent.h"

void EventController::updateActiveEventList() 
{
	while (currentEvent < eventCount && level[currentEvent].getInitTime() < *currentTime) {
		level[currentEvent].start();
		currentEvent++;
	}
}

EventController::EventController(){}
//                              ( ^ )

EventController::EventController(float* currentTime, int eventCount, LevelEvent* level)
{
	this->level = level;
	this->currentTime = currentTime;
	this->eventCount = eventCount;
	this->currentEvent = 0;
}

