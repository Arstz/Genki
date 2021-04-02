#include "LevelEvent.h"
#include "AnimationController.h"
#include "ShapeController.h"

//LevelEvent

std::list<ShapeGroup>::iterator* LevelEvent::shapeGroups = nullptr;

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

void LevelEvent::write(std::ofstream& fout) {}

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

CameraAnimationEvent* CameraAnimationEvent::create(Animation animation, uint valueNum, float initTime) {
	return new CameraAnimationEvent(animation, valueNum, initTime);
}

void CameraAnimationEvent::start() {
	AnimationController::add(AnimationTask(animation, ShapeController::getCameraValuePointer(valueNum)));
}

/*
void CameraAnimationEvent::write(std::ofstream& fout) {
	fout.write((char*)(&valueNum), sizeof(uint));

	fout.write((char*)(&animation->keyCount), sizeof(int));

	fout.write((char*)(animation->timeKeys), sizeof(int) * animation->keyCount);
	fout.write((char*)(animation->stateKeys), sizeof(int) * animation->keyCount);
}
*/

//ShapeSpawnEvent

ShapeSpawnEvent::ShapeSpawnEvent() {}

ShapeSpawnEvent* ShapeSpawnEvent::create(Shape shape, int shapeGroupID, int targetShapeGroupID, float initTime) {
	return new ShapeSpawnEvent(shape, shapeGroupID, targetShapeGroupID, initTime);
}

ShapeSpawnEvent::ShapeSpawnEvent(
	Shape shape, 
	int shapeGroupID,
	int targetShapeGroupID,
	float initTime
) : LevelEvent(initTime) {
	this->shapeGroupID = shapeGroupID;
	this->targetShapeGroupID = targetShapeGroupID;
	this->shape = shape;
	this->type = LevelEventType::SHAPE_SPAWN;
}

void ShapeSpawnEvent::start() {
	if (targetShapeGroupID) shapeGroups[shapeGroupID] = ShapeController::addShapeGroup(ShapeGroup(shape), shapeGroups[targetShapeGroupID]);
	else shapeGroups[shapeGroupID] = ShapeController::addShapeGroup(ShapeGroup(shape));
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

ShapeGroupSpawnEvent::ShapeGroupSpawnEvent() {}
ShapeGroupSpawnEvent::ShapeGroupSpawnEvent(
	ShapeGroup shapeGroup,
	int shapeGroupID,
	int targetShapeGroupID,
	float initTime
): LevelEvent(initTime) {
	this->shapeGroupID = shapeGroupID;
	this->shapeGroup = shapeGroup;
	this->type = LevelEventType::SHAPE_SPAWN;
}

ShapeGroupSpawnEvent* ShapeGroupSpawnEvent::create(ShapeGroup shapeGroup, int shapeGroupID, int targetShapeGroupID, float initTime) {
	return new ShapeGroupSpawnEvent(shapeGroup, shapeGroupID, targetShapeGroupID, initTime);
}

void ShapeGroupSpawnEvent::start() {
	if (targetShapeGroupID) shapeGroups[shapeGroupID] = ShapeController::addShapeGroup(shapeGroup, shapeGroups[targetShapeGroupID]);
	else shapeGroups[shapeGroupID] = ShapeController::addShapeGroup(shapeGroup);
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

//ShapeGroupDestructionEvent

ShapeGroupDestructionEvent::ShapeGroupDestructionEvent() {}
ShapeGroupDestructionEvent::ShapeGroupDestructionEvent(int shapeGroupID, float initTime) : LevelEvent(initTime) {
	this->shapeGroupID = shapeGroupID;
	this->type = LevelEventType::SHAPE_DESTRUCTION;
}

ShapeGroupDestructionEvent* ShapeGroupDestructionEvent::create(int shapeGroupID, float initTime) {
	return new ShapeGroupDestructionEvent(shapeGroupID, initTime);
}

void ShapeGroupDestructionEvent::start() {
	ShapeController::removeShapeGroup(shapeGroups[shapeGroupID]);
}

/*
void ShapeDestructionEvent::write(std::ofstream& fout) {
	fout.write((char*)(&shapeID), sizeof(int));
}
*/

//ShapeAnimationEvent

ShapeAnimationEvent::ShapeAnimationEvent() {}
ShapeAnimationEvent::ShapeAnimationEvent(
	Animation animation,
	AnimatedValueType animatedValueType,
	int shapeGroupID,
	int animatedValueID,
	int shapeNum,
	int vertexNum,
	int valueNum,
	float initTime
) : LevelEvent(initTime) {
	this->animation = animation;
	this->animatedValueType = animatedValueType;
	this->shapeGroupID = shapeGroupID;
	this->animatedValueID = animatedValueID;
	this->shapeNum = shapeNum;
	this->vertexNum = vertexNum;
	this->valueNum = valueNum;
	this->type = LevelEventType::SHAPE_ANIMATION;
}

ShapeAnimationEvent* ShapeAnimationEvent::create(
	Animation animation,
	AnimatedValueType animatedValueType,
	int shapeGroupID,
	int animatedValueID,
	int shapeNum,
	int vertexNum,
	int valueNum,
	float initTime
) {
	return new ShapeAnimationEvent(
		animation,
		animatedValueType,
		shapeGroupID,
		animatedValueID,
		shapeNum,
		vertexNum,
		valueNum,
		initTime
	);
}

void ShapeAnimationEvent::start() {
	float* target;

	Shape* shape = &(*shapeGroups[shapeGroupID]).getShapesPointer()[shapeNum];

	switch (animatedValueType) {
	case AnimatedValueType::VERTEX_POSITION:
		target = &shape->getVertexCoordsPointer()[vertexNum * 2 + valueNum];
		break;
	case AnimatedValueType::VERTEX_COLOR:
		target = &shape->getVertexColorsPointer()[vertexNum * 4 + valueNum];
		break;
	case AnimatedValueType::ALPHA_CHANNEL:
		target = shape->getAlphaChannelPointer();
		break;
	case AnimatedValueType::POSITION_X:
		target = shape->getPositionXpointer();
		break;
	case AnimatedValueType::POSITION_Y:
		target = shape->getPositionYpointer();
		break;
	default:
		throw "WRONG ANIMATED VALUE TYPE";
		break;
	}
	AnimationController::add(AnimationTask(animation, target));
}

/*
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
*/

//ShapeAnimationEvent

ShapeGroupAnimationEvent::ShapeGroupAnimationEvent() {}
ShapeGroupAnimationEvent::ShapeGroupAnimationEvent(
	Animation animation,
	AnimatedValueType animatedValueType,
	int shapeGroupID,
	float initTime
): LevelEvent(initTime) {
	this->animation = animation;
	this->animatedValueType = animatedValueType;
	this->shapeGroupID = shapeGroupID;
	this->type = LevelEventType::SHAPE_ANIMATION;
}

ShapeGroupAnimationEvent* ShapeGroupAnimationEvent::create(
	Animation animation,
	AnimatedValueType animatedValueType,
	int shapeGroupID,
	float initTime
) {
	return new ShapeGroupAnimationEvent(
		animation,
		animatedValueType,
		shapeGroupID,
		initTime
	);
}

void ShapeGroupAnimationEvent::start() {
	float* target;

	ShapeGroup* shapeGroup = &(*shapeGroups[shapeGroupID]);

	switch (animatedValueType) {
	case AnimatedValueType::ALPHA_CHANNEL:
		target = shapeGroup->getAlphaChannelPointer();
		break;
	case AnimatedValueType::POSITION_X:
		target = shapeGroup->getPositionXpointer();
		break;
	case AnimatedValueType::POSITION_Y:
		target = shapeGroup->getPositionYpointer();
		break;
	default:
		throw "WRONG ANIMATED VALUE TYPE";
		break;
	}
	AnimationController::add(AnimationTask(animation, target));
}

/*
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
*/

//PlayerBindingEvent

Player* PlayerBindingEvent::player = nullptr;

PlayerBindingEvent::PlayerBindingEvent() {}
PlayerBindingEvent::PlayerBindingEvent(int shapeGroupID, float initTime) : LevelEvent(initTime) {
	this->shapeGroupID = shapeGroupID;
	this->type = LevelEventType::PLAYER_BINDING;
}
PlayerBindingEvent* PlayerBindingEvent::create(int shapeGroupID, float initTime) {
	return new PlayerBindingEvent(shapeGroupID, initTime);
}
/*
void PlayerBindingEvent::write(std::ofstream& fout) {
	fout.write((char*)(&shapeGroupID), sizeof(int));
}
*/
void PlayerBindingEvent::start() {
	player->setTarget(
		(*(shapeGroups[shapeGroupID])).getPositionXpointer(),
		(*(shapeGroups[shapeGroupID])).getPositionYpointer()
	);
}

//BackgroundColorAnimationEvent

BackgroundColorAnimationEvent::BackgroundColorAnimationEvent() {}
BackgroundColorAnimationEvent::BackgroundColorAnimationEvent(uint animatedValueID, Animation animation, float initTime) : LevelEvent(initTime) {
	this->type = LevelEventType::BACKGROUND_COLOR_ANIMATION;
	this->animation = animation;
	this->animatedValueID = animatedValueID;
}

BackgroundColorAnimationEvent* BackgroundColorAnimationEvent::create(uint animatedValueID, Animation animation, float initTime) {
	return new BackgroundColorAnimationEvent(animatedValueID, animation, initTime);
}

void BackgroundColorAnimationEvent::start() {
	AnimationController::add(AnimationTask(animation, Window::getBackgroundColorValuePointer(animatedValueID)));
}

/*
void BackgroundColorAnimationEvent::write(std::ofstream& fout) {
	fout.write((char*)(&animatedValueID), sizeof(uint));
}
*/
