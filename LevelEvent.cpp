#include "LevelEvent.h"
#include "AnimationController.h"
#include "Graphics.h"

//LevelEvent

std::list<Shape*>::iterator* LevelEvent::dynamicShapes = nullptr;

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

void LevelEvent::write(std::ofstream& fout) {}

void LevelEvent::start() {}

//CameraAnimationEvent

CameraAnimationEvent::CameraAnimationEvent() {}
CameraAnimationEvent::CameraAnimationEvent(
	Animation* animation, 
	uint valueNum, 
	float initTime
) : LevelEvent::LevelEvent(initTime) {
	this->animation = animation;
	this->valueNum = valueNum;
	this->type = LevelEventType::CAMERA_ANIMATION;
}

void CameraAnimationEvent::write(std::ofstream& fout) {
	fout.write((char*)(&valueNum), sizeof(uint));

	fout.write((char*)(&animation->keyCount), sizeof(int));

	fout.write((char*)(animation->timeKeys), sizeof(int) * animation->keyCount);
	fout.write((char*)(animation->stateKeys), sizeof(int) * animation->keyCount);
}

void CameraAnimationEvent::start() {
	AnimationController::add(new AnimationTask(*animation, Graphics::getCameraValuePointer(valueNum)));
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

void ShapeSpawnEvent::write(std::ofstream& fout) {
	fout.write((char*)(&shape->vertexCount), sizeof(uint));
	fout.write((char*)(shape->vertexCoords), sizeof(float) * shape->vertexCount * 2);
	fout.write((char*)(shape->vertexColors), sizeof(float) * shape->vertexCount * 4);
	fout.write((char*)(&shape->EBOsize), sizeof(uint));
	fout.write((char*)(shape->vertexIDs), sizeof(uint) * shape->EBOsize);
	fout.write((char*)(&shapeID), sizeof(int));
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

void ShapeDestructionEvent::write(std::ofstream& fout) {
	fout.write((char*)(&shapeID), sizeof(int));
}

void ShapeDestructionEvent::start() {
	Graphics::removeShape(dynamicShapes[shapeID]);
}

//ShapeAnimationEvent

ShapeAnimationEvent::ShapeAnimationEvent() {}
ShapeAnimationEvent::ShapeAnimationEvent(
	Animation* animation, 
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

void ShapeAnimationEvent::write(std::ofstream& fout) {
	fout.write((char*)(&shapeID), sizeof(int));
	fout.write((char*)(&AnimatedValueID), sizeof(int));
	fout.write((char*)(&vertexNum), sizeof(int));
	fout.write((char*)(&channelNum), sizeof(int));
	fout.write((char*)(&animatedValueType), sizeof(AnimatedValueType));

	fout.write((char*)(&animation->keyCount), sizeof(int));

	fout.write((char*)(animation->timeKeys), sizeof(int) * animation->keyCount);
	fout.write((char*)(animation->stateKeys), sizeof(int) * animation->keyCount);
}

void ShapeAnimationEvent::start() {
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
	AnimationController::add(new AnimationTask(*animation, target));
}

//PlayerBindingEvent

Player* PlayerBindingEvent::player = nullptr;

PlayerBindingEvent::PlayerBindingEvent() {}
PlayerBindingEvent::PlayerBindingEvent(int shapeID, float initTime) : LevelEvent(initTime) {
	this->shapeID = shapeID;
	this->type = LevelEventType::PLAYER_BINDING;
}

void PlayerBindingEvent::write(std::ofstream& fout) {
	fout.write((char*)(&shapeID), sizeof(int));
}

void PlayerBindingEvent::start() {
	player->bind(*(dynamicShapes[shapeID]));
}

//BackgroundColorAnimationEvent

BackgroundColorAnimationEvent::BackgroundColorAnimationEvent() {}
BackgroundColorAnimationEvent::BackgroundColorAnimationEvent(uint animatedValueID, Animation* animation, float initTime) : LevelEvent(initTime) {
	this->type = LevelEventType::BACKGROUND_COLOR_ANIMATION;
	this->animatedValueID = animatedValueID;
}

void BackgroundColorAnimationEvent::write(std::ofstream& fout) {
	fout.write((char*)(&animatedValueID), sizeof(uint));
}

void BackgroundColorAnimationEvent::start() {
	AnimationController::add(new AnimationTask(*animation, Graphics::getBackgroundColorValuePointer(animatedValueID)));
}
