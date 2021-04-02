#include "LevelEvent.h"
#include "AnimationController.h"
#include "ShapeController.h"
#include "ByteArray.h"

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

std::vector<char> LevelEvent::getByteArray() {
	return std::vector<char>();
}

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

CameraAnimationEvent* CameraAnimationEvent::create(char* byteArray, unsigned int& offset)
{
	return nullptr;
}

void CameraAnimationEvent::start() {
	AnimationController::add(AnimationTask(animation, ShapeController::getCameraValuePointer(valueNum)));
}

std::vector<char> CameraAnimationEvent::getByteArray() {
	std::vector<char> animationArray = animation.getByteArray();
	unsigned int byteArraySize = animationArray.size() + sizeof(valueNum);

	std::vector<char> byteArray(byteArraySize);

	unsigned int offset = 0;

	writeToByteArray(byteArray, (char*)&valueNum, offset, sizeof(valueNum));
	writeToByteArray(byteArray, animationArray, offset);

	return byteArray;
}

//ShapeSpawnEvent

ShapeSpawnEvent::ShapeSpawnEvent() {}

ShapeSpawnEvent* ShapeSpawnEvent::create(Shape shape, int shapeGroupID, int targetShapeGroupID, float initTime) {
	return new ShapeSpawnEvent(shape, shapeGroupID, targetShapeGroupID, initTime);
}

ShapeSpawnEvent* ShapeSpawnEvent::create(char* byteArray, unsigned int& offset)
{
	return nullptr;
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

std::vector<char> ShapeSpawnEvent::getByteArray() {
	std::vector<char> shapeArray = shape.getByteArray();
	unsigned int byteArraySize = 
		shapeArray.size() + 
		sizeof(shapeGroupID) + 
		sizeof(targetShapeGroupID);

	std::vector<char> byteArray(byteArraySize);

	unsigned int offset = 0;

	writeToByteArray(byteArray, (char*)&shapeGroupID, offset, sizeof(shapeGroupID));
	writeToByteArray(byteArray, (char*)&targetShapeGroupID, offset, sizeof(targetShapeGroupID));
	writeToByteArray(byteArray, shapeArray, offset);

	return byteArray;
}

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

ShapeGroupSpawnEvent* ShapeGroupSpawnEvent::create(char* byteArray, unsigned int& offset)
{
	return nullptr;
}

std::vector<char> ShapeGroupSpawnEvent::getByteArray() {
	std::vector<char> shapeGroupArray = shapeGroup.getByteArray();
	unsigned int byteArraySize =
		shapeGroupArray.size() +
		sizeof(shapeGroupID) +
		sizeof(targetShapeGroupID);

	std::vector<char> byteArray(byteArraySize);

	unsigned int offset = 0;

	writeToByteArray(byteArray, (char*)&shapeGroupID, offset, sizeof(shapeGroupID));
	writeToByteArray(byteArray, (char*)&targetShapeGroupID, offset, sizeof(targetShapeGroupID));
	writeToByteArray(byteArray, shapeGroupArray, offset);

	return byteArray;
}

void ShapeGroupSpawnEvent::start() {
	if (targetShapeGroupID) shapeGroups[shapeGroupID] = ShapeController::addShapeGroup(shapeGroup, shapeGroups[targetShapeGroupID]);
	else shapeGroups[shapeGroupID] = ShapeController::addShapeGroup(shapeGroup);
}

//ShapeGroupDestructionEvent

ShapeGroupDestructionEvent::ShapeGroupDestructionEvent() {}
ShapeGroupDestructionEvent::ShapeGroupDestructionEvent(int shapeGroupID, float initTime) : LevelEvent(initTime) {
	this->shapeGroupID = shapeGroupID;
	this->type = LevelEventType::SHAPE_DESTRUCTION;
}

ShapeGroupDestructionEvent* ShapeGroupDestructionEvent::create(int shapeGroupID, float initTime) {
	return new ShapeGroupDestructionEvent(shapeGroupID, initTime);
}

ShapeGroupDestructionEvent* ShapeGroupDestructionEvent::create(char* byteArray, unsigned int& offset)
{
	return nullptr;
}

void ShapeGroupDestructionEvent::start() {
	ShapeController::removeShapeGroup(shapeGroups[shapeGroupID]);
}

std::vector<char> ShapeGroupDestructionEvent::getByteArray() {
	unsigned int byteArraySize = sizeof(shapeGroupID);
	std::vector<char> byteArray(byteArraySize);

	unsigned int offset = 0;

	writeToByteArray(byteArray, (char*)&shapeGroupID, offset, sizeof(shapeGroupID));

	return byteArray;
}

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

ShapeAnimationEvent* ShapeAnimationEvent::create(char* byteArray, unsigned int& offset)
{
	return nullptr;
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

std::vector<char> ShapeAnimationEvent::getByteArray() {
	std::vector<char> animationArray = animation.getByteArray();
	unsigned int byteArraySize =
		animationArray.size() +
		sizeof(animatedValueType) +
		sizeof(shapeGroupID) +
		sizeof(animatedValueID) +
		sizeof(shapeNum) +
		sizeof(vertexNum) +
		sizeof(valueNum);

	std::vector<char> byteArray(byteArraySize);

	unsigned int offset = 0;

	writeToByteArray(byteArray, (char*)&animatedValueType, offset, sizeof(animatedValueType));
	writeToByteArray(byteArray, (char*)&shapeGroupID, offset, sizeof(shapeGroupID));
	writeToByteArray(byteArray, (char*)&animatedValueID, offset, sizeof(animatedValueID));
	writeToByteArray(byteArray, (char*)&shapeNum, offset, sizeof(shapeNum));
	writeToByteArray(byteArray, (char*)&vertexNum, offset, sizeof(vertexNum));
	writeToByteArray(byteArray, (char*)&valueNum, offset, sizeof(valueNum));
	writeToByteArray(byteArray, animationArray, offset);

	return byteArray;
}

//ShapeGroupAnimationEvent

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

ShapeGroupAnimationEvent* ShapeGroupAnimationEvent::create(char* byteArray, unsigned int& offset)
{
	return nullptr;
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

std::vector<char> ShapeGroupAnimationEvent::getByteArray() {
	std::vector<char> animationArray = animation.getByteArray();
	unsigned int byteArraySize =
		animationArray.size() +
		sizeof(animatedValueType) +
		sizeof(shapeGroupID);

	std::vector<char> byteArray(byteArraySize);

	unsigned int offset = 0;

	writeToByteArray(byteArray, (char*)&animatedValueType, offset, sizeof(animatedValueType));
	writeToByteArray(byteArray, (char*)&shapeGroupID, offset, sizeof(shapeGroupID));
	writeToByteArray(byteArray, animationArray, offset);

	return byteArray;
}

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

PlayerBindingEvent* PlayerBindingEvent::create(char* byteArray, unsigned int& offset)
{
	return nullptr;
}

void PlayerBindingEvent::start() {
	player->setTarget(
		(*(shapeGroups[shapeGroupID])).getPositionXpointer(),
		(*(shapeGroups[shapeGroupID])).getPositionYpointer()
	);
}

std::vector<char> PlayerBindingEvent::getByteArray() {
	unsigned int byteArraySize = sizeof(shapeGroupID);
	std::vector<char> byteArray(byteArraySize);

	unsigned int offset = 0;

	writeToByteArray(byteArray, (char*)&shapeGroupID, offset, sizeof(shapeGroupID));

	return byteArray;
}

//BackgroundColorAnimationEvent

BackgroundColorAnimationEvent::BackgroundColorAnimationEvent() {}
BackgroundColorAnimationEvent::BackgroundColorAnimationEvent(uint valueNum, Animation animation, float initTime) : LevelEvent(initTime) {
	this->type = LevelEventType::BACKGROUND_COLOR_ANIMATION;
	this->animation = animation;
	this->valueNum = valueNum;
}

BackgroundColorAnimationEvent* BackgroundColorAnimationEvent::create(uint valueNum, Animation animation, float initTime) {
	return new BackgroundColorAnimationEvent(valueNum, animation, initTime);
}

BackgroundColorAnimationEvent* BackgroundColorAnimationEvent::create(char* byteArray, unsigned int& offset)
{
	return nullptr;
}

void BackgroundColorAnimationEvent::start() {
	AnimationController::add(AnimationTask(animation, Window::getBackgroundColorValuePointer(valueNum)));
}

std::vector<char> BackgroundColorAnimationEvent::getByteArray() {
	std::vector<char> animationArray = animation.getByteArray();
	unsigned int byteArraySize = animationArray.size() + sizeof(valueNum);

	std::vector<char> byteArray(byteArraySize);

	unsigned int offset = 0;

	writeToByteArray(byteArray, (char*)&valueNum, offset, sizeof(valueNum));
	writeToByteArray(byteArray, animationArray, offset);

	return byteArray;
}
