#include "LevelEvent.h"
#include "..\AnimationController.h"
#include "..\ShapeController.h"
#include "..\ByteArray.h"

//LevelEvent

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

std::vector<char> LevelEvent::getByteArray() {
	return std::vector<char>();
}

void LevelEvent::destroy()
{
//	delete[] shapeGroups;
}

void LevelEvent::write(std::ofstream& fout) {}
