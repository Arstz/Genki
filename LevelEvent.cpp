#include "LevelEvent.h"
#include "AnimationController.h"
#include "Graphics.h"

//LevelEvent

std::list<Shape*>::iterator* LevelEvent::dynamicShapes = new std::list<Shape*>::iterator[1];

float LevelEvent::getInitTime() {
	return initTime;
}

LevelEvent::LevelEvent() {}
LevelEvent::LevelEvent(float initTime) {
	this->initTime = initTime;
	this->type = LevelEventType::EMPTY;
}

LevelEventType LevelEvent::getType() {
	return type;
}

void LevelEvent::start() {}

//CameraAnimationEvent

CameraAnimationEvent::CameraAnimationEvent() {}
CameraAnimationEvent::CameraAnimationEvent(
	Animation animation, 
	uint valueNum, 
	float initTime
) : LevelEvent::LevelEvent(initTime) {
	this->animation = animation;
	this->valueNum = valueNum;
	this->initTime = initTime;
}

void CameraAnimationEvent::start() {
	AnimationController::add(new AnimationTask(animation, Graphics::getCameraValuePointer(valueNum)));
}

//ShapeSpawnEvent

ShapeSpawnEvent::ShapeSpawnEvent() {}
ShapeSpawnEvent::ShapeSpawnEvent(
	Shape* shape, 
	int shapeID,
	float initTime
) : LevelEvent(initTime) {
	this->shapeID = shapeID;
	this->shape = shape;
	this->type = LevelEventType::SHAPE_SPAWN;
}

void ShapeSpawnEvent::start() {
	dynamicShapes[shapeID] = Graphics::addShape(shape);
}

//ShapeDestructionEvent

ShapeDestructionEvent::ShapeDestructionEvent() {}
ShapeDestructionEvent::ShapeDestructionEvent(int shapeID, float initTime) : LevelEvent(initTime) {
	this->shapeID = shapeID;
	this->type = LevelEventType::SHAPE_DESTRUCTION;
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
	this->type = LevelEventType::SHAPE_ANIMATION;
}

void ShapeAnimationEvent::start()
{
	float* target;
	switch(animatedValueType)
	{
	case VERTEX:
		target = (*dynamicShapes[shapeID])->getPositionPointer(vertexNum, channelNum);
		break;
	case COLOR:
		target = (*dynamicShapes[shapeID])->getColorPointer(vertexNum, channelNum);
		break;
	default:
		throw "WRONG ANIMATED VALUE TYPE";
		break;
	}
	AnimationController::add(new AnimationTask(animation, target));
}

//PlayerBindingEvent

Player* PlayerBindingEvent::player = nullptr;

PlayerBindingEvent::PlayerBindingEvent() {}
PlayerBindingEvent::PlayerBindingEvent(int shapeID, float initTime) : LevelEvent(initTime) {
	this->shapeID = shapeID;
	this->type = LevelEventType::PLAYER_BINDING;
}

void PlayerBindingEvent::start() {
	player->bind(*(dynamicShapes[shapeID]));
}