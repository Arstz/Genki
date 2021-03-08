#include "EventController.h"

void EventController::updateEvents(){
	for (auto &levelEvent : activeEvents){
		levelEvent.update();
	}
}

void EventController::updateActiveEventList() {
	while (currentEvent < eventCount && level[currentEvent].initTime < *currentTime) {
		currentEvent++;
	}
}

EventController::EventController(){}

EventController::EventController(float& currentTime)
{
	this->currentTime = &currentTime;
};
