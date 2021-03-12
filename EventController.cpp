#include "EventController.h"
#include "LevelEvent.h"
#include <vector>

void EventController::updateActiveEventList() 
{
	while (currentEvent < eventCount && level[currentEvent]->getInitTime() < *currentTime) {
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

