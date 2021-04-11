#include "LevelEvent.h"

std::list<ShapeGroup>::iterator* LevelEvent::shapeGroups = nullptr;

float LevelEvent::getInitTime() {
	return initTime;
}

LevelEvent::LevelEvent(){
	this->initTime = 0;
	this->type = LevelEventType::EMPTY;
}

LevelEvent::~LevelEvent() {}

LevelEvent::LevelEvent(float initTime) {
	this->initTime = initTime;
	this->type = LevelEventType::EMPTY;
}

LevelEventType LevelEvent::getType() {
	return type;
}

void LevelEvent::start() {}

ByteArray LevelEvent::getByteArray() {
	return ByteArray();
}
