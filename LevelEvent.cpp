#include "LevelEvent.h"
#include "AnimationController.h"
#include "ShapeController.h"

//LevelEvent

std::list<ShapeGroup*>::iterator* LevelEvent::shapeGroups = nullptr;

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
	Animation animation, 
	uint valueNum, 
	float initTime
) : LevelEvent::LevelEvent(initTime) {
	this->animation = animation;
	this->valueNum = valueNum;
	this->type = LevelEventType::CAMERA_ANIMATION;
}
/*
void CameraAnimationEvent::write(std::ofstream& fout) {
	fout.write((char*)(&valueNum), sizeof(uint));

	fout.write((char*)(&animation->keyCount), sizeof(int));

	fout.write((char*)(animation->timeKeys), sizeof(int) * animation->keyCount);
	fout.write((char*)(animation->stateKeys), sizeof(int) * animation->keyCount);
}
*/
CameraAnimationEvent* CameraAnimationEvent::create(Animation animation, uint valueNum, float initTime) {
	return new CameraAnimationEvent(animation, valueNum, initTime);
}

void CameraAnimationEvent::start() {
	AnimationController::add(new AnimationTask(animation, ShapeController::getCameraValuePointer(valueNum)));
}

//ShapeSpawnEvent

ShapeSpawnEvent::ShapeSpawnEvent() {}

ShapeSpawnEvent* ShapeSpawnEvent::create(Shape shape, int shapeGroupID, float initTime) {
	return new ShapeSpawnEvent(shape, shapeGroupID, initTime);
}

ShapeSpawnEvent::ShapeSpawnEvent(
	Shape shape, 
	int shapeGroupID,
	float initTime
) : LevelEvent(initTime) {
	this->shapeGroupID = shapeGroupID;
	this->shape = shape;
	this->type = LevelEventType::SHAPE_SPAWN;
}
/*
void ShapeSpawnEvent::write(std::ofstream& fout) {
	fout.write((char*)(&shape->vertexCount), sizeof(uint));
	fout.write((char*)(shape->vertexCoords), sizeof(float) * shape->vertexCount * 2);
	fout.write((char*)(shape->vertexColors), sizeof(float) * shape->vertexCount * 4);
	fout.write((char*)(&shape->EBOsize), sizeof(uint));
	fout.write((char*)(shape->vertexIDs), sizeof(uint) * shape->EBOsize);
	fout.write((char*)(&shapeID), sizeof(int));
}
*/
void ShapeSpawnEvent::start() {
	shapeGroups[shapeGroupID] = ShapeController::addShape(shape);
}

ShapeGroupSpawnEvent::ShapeGroupSpawnEvent() {}
ShapeGroupSpawnEvent::ShapeGroupSpawnEvent(
	ShapeGroup shapeGroup,
	int shapeGroupID,
	float initTime
): LevelEvent(initTime) {
	this->shapeGroupID = shapeGroupID;
	this->shapeGroup = shapeGroup;
	this->type = LevelEventType::SHAPE_SPAWN;
}
ShapeGroupSpawnEvent* ShapeGroupSpawnEvent::create(ShapeGroup shapeGroup, int shapeGroupID, float initTime) {
	return new ShapeGroupSpawnEvent(shapeGroup, shapeGroupID, initTime);
}
/*
void ShapeSpawnEvent::write(std::ofstream& fout) {
	fout.write((char*)(&shape->vertexCount), sizeof(uint));
	fout.write((char*)(shape->vertexCoords), sizeof(float) * shape->vertexCount * 2);
	fout.write((char*)(shape->vertexColors), sizeof(float) * shape->vertexCount * 4);
	fout.write((char*)(&shape->EBOsize), sizeof(uint));
	fout.write((char*)(shape->vertexIDs), sizeof(uint) * shape->EBOsize);
	fout.write((char*)(&shapeID), sizeof(int));
}
*/

void ShapeGroupSpawnEvent::start() {
	shapeGroups[shapeGroupID] = ShapeController::addShapeGroup(&shapeGroup);
}

//ShapeGroupDestructionEvent

ShapeGroupDestructionEvent::ShapeGroupDestructionEvent() {}
ShapeGroupDestructionEvent::ShapeGroupDestructionEvent(int shapeGroupID, float initTime) : LevelEvent(initTime) {
	this->shapeGroupID = shapeGroupID;
	this->type = LevelEventType::SHAPE_DESTRUCTION;
}
/*
void ShapeDestructionEvent::write(std::ofstream& fout) {
	fout.write((char*)(&shapeID), sizeof(int));
}
*/
ShapeGroupDestructionEvent* ShapeGroupDestructionEvent::create(int shapeGroupID, float initTime) {
	return new ShapeGroupDestructionEvent(shapeGroupID, initTime);
}

void ShapeGroupDestructionEvent::start() {
	ShapeController::removeShapeGroup(shapeGroups[shapeGroupID]);
}

//ShapeAnimationEvent
/*
ShapeAnimationEvent::ShapeAnimationEvent() {}
ShapeAnimationEvent::ShapeAnimationEvent(
	Animation animation,
	AnimatedValueType animatedValueType,
	uint* shapePath,
	uint pathSize,
	int animatedValueID,
	int vertexNum,
	int valueNum,
	float initTime
) : LevelEvent(initTime) {
	this->animation = animation;
	this->animatedValueType = animatedValueType;

	this->shapePath = new uint[pathSize];
	for (int i = 0; i < pathSize; i++) this->shapePath[i] = shapePath[i];

	this->animatedValueID = animatedValueID;
	this->vertexNum = vertexNum;
	this->valueNum = valueNum;
	this->type = LevelEventType::SHAPE_ANIMATION;
}

ShapeAnimationEvent* ShapeAnimationEvent::create(
	Animation animation,
	AnimatedValueType animatedValueType,
	uint* shapePath,
	uint pathSize,
	int animatedValueID, 
	int vertexNum,
	int valueNum,
	float initTime
) {
	return new ShapeAnimationEvent(
		animation,
		animatedValueType,
		shapePath,
		pathSize,
		animatedValueID,
		vertexNum,
		valueNum,
		initTime
	);
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
	case AnimatedValueType::VERTEX_POSITION:
		break;
	case AnimatedValueType::VERTEX_COLOR:
		break;
	case AnimatedValueType::ALPHA_CHANNEL:
		break;
	case AnimatedValueType::POSITION_X:
		break;
	case AnimatedValueType::POSITION_Y:
		break;
	default:
		throw "WRONG ANIMATED VALUE TYPE";
		break;
	}
	AnimationController::add(new AnimationTask(animation, target));
}
*/
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
	player->setTarget(
		(*(shapeGroups[shapeID]))->getPositionXpointer(),
		(*(shapeGroups[shapeID]))->getPositionYpointer()
	);
}

//BackgroundColorAnimationEvent

BackgroundColorAnimationEvent::BackgroundColorAnimationEvent() {}
BackgroundColorAnimationEvent::BackgroundColorAnimationEvent(uint animatedValueID, Animation animation, float initTime) : LevelEvent(initTime) {
	this->type = LevelEventType::BACKGROUND_COLOR_ANIMATION;
	this->animatedValueID = animatedValueID;
}

BackgroundColorAnimationEvent* BackgroundColorAnimationEvent::create(uint animatedValueID, Animation animation, float initTime) {
	return new BackgroundColorAnimationEvent(animatedValueID, animation, initTime);
}

/*
void BackgroundColorAnimationEvent::write(std::ofstream& fout) {
	fout.write((char*)(&animatedValueID), sizeof(uint));
}
*/

void BackgroundColorAnimationEvent::start() {
	AnimationController::add(new AnimationTask(animation, Window::getBackgroundColorValuePointer(animatedValueID)));
}

