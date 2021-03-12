#include "EventController.h"

/*
void EventController::updateEvents(){
	for (auto &levelEvent : activeEvents){
		levelEvent.update();
	}
}
*/

void EventController::updateActiveEventList() {
	while (currentEvent < eventCount && level[currentEvent].getInitTime() < *currentTime) {
		currentEvent++;
	}
}

EventController::EventController(){
}

EventController::EventController(float& currentTime)
{
	this->currentTime = &currentTime;
}

void EventController::startEvent(LevelEvent &levelEvent)
{
	
	
}
