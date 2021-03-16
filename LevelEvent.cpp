#include "LevelEvent.h"
#include "Graphics.h"

//LevelEvent

std::list<AnimationTask>* LevelEvent::animationTasks = nullptr;
std::list<Shape>::iterator* LevelEvent::dynamicShapes = new std::list<Shape>::iterator[1];

float LevelEvent::getInitTime() {
	return initTime;
}

LevelEvent::LevelEvent() {}
LevelEvent::LevelEvent(float initTime) {
	this->initTime = initTime;
}

void LevelEvent::start() {}

//CameraAnimationEvent

void CameraAnimationEvent::start() {

}

//ShapeSpawnEvent

ShapeSpawnEvent::ShapeSpawnEvent() {}
ShapeSpawnEvent::ShapeSpawnEvent(
	Shape shape, 
	int shapeID,
	float initTime
) : LevelEvent(initTime) {
	this->shapeID = shapeID;
	this->shape = shape;
}

void ShapeSpawnEvent::start() {
	dynamicShapes[shapeID] = Graphics::addShape(shape);
}

//ShapeDestructionEvent

ShapeDestructionEvent::ShapeDestructionEvent() {}
ShapeDestructionEvent::ShapeDestructionEvent(int shapeID, float initTime) : LevelEvent(initTime) {
	this->shapeID = shapeID;
}

void ShapeDestructionEvent::start() {
	Graphics::removeShape(dynamicShapes[shapeID]);
}

//ShapeAnimationEvent

ShapeAnimationEvent::ShapeAnimationEvent() {}
ShapeAnimationEvent::ShapeAnimationEvent(
	Animation animation, 
	AnimatedValueType animatedValueType, 
	int AnimatedValueID, 
	int shapeID,
	int vertexNum,
	int channelNum
) : LevelEvent(initTime) {
	this->animation = animation;
	this->animatedValueType = animatedValueType;
	this->AnimatedValueID = AnimatedValueID;
	this->shapeID = shapeID;
	this->vertexNum = vertexNum;
	this->channelNum = channelNum;
}

void ShapeAnimationEvent::start()
{
	float* target;
	switch(animatedValueType)
	{
	case VERTEX:
		target = dynamicShapes[shapeID]->getPositionPointer(vertexNum, channelNum);
		break;
	case COLOR:
		target = dynamicShapes[shapeID]->getColorPointer(vertexNum, channelNum);
		break;
	default:
		throw "WRONG ANIMATED VALUE TYPE";
		break;
	}
	animationTasks->push_back(AnimationTask(animation, target));
}

//PlayerBindingEvent

Player* PlayerBindingEvent::player = nullptr;

PlayerBindingEvent::PlayerBindingEvent() {}
PlayerBindingEvent::PlayerBindingEvent(int shapeID, float initTime) : LevelEvent(initTime) {
	this->shapeID = shapeID;
}

void PlayerBindingEvent::start() {
	player->shape = &(*(dynamicShapes[shapeID]));
}