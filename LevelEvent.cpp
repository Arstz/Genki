#include "LevelEvent.h"
#include "Graphics.h"

//LevelEvent

std::list<AnimationTask>* LevelEvent::animationTasks = nullptr;
std::list<Shape>::iterator* LevelEvent::dynamicShapes = nullptr;

LevelEvent* LevelEvent::load() {
	return nullptr;
}

void LevelEvent::start() {

}

float LevelEvent::getInitTime() {
	return initTime;
}

LevelEvent::LevelEvent() {

}

LevelEvent::LevelEvent(float initTime) {
	this->initTime = initTime;
}

//CameraAnimationEvent

void CameraAnimationEvent::start() {

}

//ShapeSpawnEvent

void ShapeSpawnEvent::start() {
	dynamicShapes[shapeID] = Graphics::addShape(shape);
}

ShapeSpawnEvent::ShapeSpawnEvent() {}

ShapeSpawnEvent::ShapeSpawnEvent(
	Shape shape, 
	int shapeID,
	float initTime
) : LevelEvent(initTime) {
	this->shapeID = shapeID;
	this->shape = shape;
}

//ShapeDestructionEvent

void ShapeDestructionEvent::start() {
	Graphics::removeShape(dynamicShapes[shapeID]);
}

//ShapeAnimationEvent
void ShapeAnimationEvent::start()
{
	float* target;
	switch(animatedValueType)
	{
	case SHAPE_VERTEX_X:
		target = dynamicShapes[shapeID]->getPositionPointer(0, 0);
		break;
	case SHAPE_VERTEX_Y:
		target = dynamicShapes[shapeID]->getColorPointer(0, 0);
		break;
	default:
		throw "WRONG ANIMATED VALUE TYPE";
		break;
	}
	animationTasks->push_back(AnimationTask(animation, target));
}

//PlayerBindingEvent

Player* PlayerBindingEvent::player = nullptr;

void PlayerBindingEvent::start()
{
	player->shape = &(*(dynamicShapes[shapeID]));
}

PlayerBindingEvent::PlayerBindingEvent(int shapeID, float initTime) : LevelEvent(initTime) {
	this->shapeID = shapeID;
}
