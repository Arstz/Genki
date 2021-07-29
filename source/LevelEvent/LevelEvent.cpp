#include "LevelEvent.h"

std::list<ShapeGroup>::iterator* LevelEvent::shapeGroups = nullptr;
ShapeController* LevelEvent::shapeController = nullptr;

float LevelEvent::getInitTime() {
	return initTime;
}

void LevelEvent::setShapeController(ShapeController* shapeController) {
	LevelEvent::shapeController = shapeController;
}

void LevelEvent::setShapeGroupsSize(unsigned int size) {
	delete[] shapeGroups;
	LevelEvent::shapeGroups = new std::list<ShapeGroup>::iterator[size];
}

LevelEvent::LevelEvent(){
	this->initTime = 0;
	this->type = LevelEventType::NONE;
}

LevelEvent::~LevelEvent() {}

LevelEvent::LevelEvent(float initTime) {
	this->initTime = initTime;
	this->type = LevelEventType::NONE;
}

LevelEventType LevelEvent::getType() {
	return type;
}

void LevelEvent::start() {}

ByteArray LevelEvent::getByteArray() {
	return ByteArray();
}
