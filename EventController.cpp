#include "EventController.h"
#include "LevelEvent.h"
#include <vector>
#include <iostream>


std::vector<LevelEvent*> EventController::level;
int EventController::currentEvent = 0;
float* EventController::currentTime = nullptr;

void EventController::updateActiveEventList() 
{
	while (currentEvent < level.size() && level[currentEvent]->getInitTime() < *currentTime) {
		level[currentEvent]->start();
		currentEvent++;
	}
}