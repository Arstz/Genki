#include "EventController.h"

void EventController::updateEvents(){
	for (auto &levelEvent : activeEvents){
		levelEvent.update();
	}
}

void EventController::updateActiveEventList() {
	//while()
};
