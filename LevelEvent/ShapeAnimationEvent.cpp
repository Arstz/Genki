#include "ShapeAnimationEvent.h"
#include "..\AnimationController.h"
#include "..\ShapeController.h"
#include "..\ByteArray.h"

ShapeAnimationEvent::ShapeAnimationEvent(
	Animation animation,
	AnimatedValueType animatedValueType,
	int shapeGroupID,
	int shapeNum,
	int vertexNum,
	int valueNum,
	float initTime
): LevelEvent(initTime) {
	this->animation = animation;
	this->animatedValueType = animatedValueType;
	this->shapeGroupID = shapeGroupID;
	this->shapeNum = shapeNum;
	this->vertexNum = vertexNum;
	this->valueNum = valueNum;
	this->type = LevelEventType::SHAPE_ANIMATION;
}

ShapeAnimationEvent::ShapeAnimationEvent(
	Animation animation,
	AnimatedValueType animatedValueType,
	int shapeGroupID,
	int shapeNum,
	int valueNum,
	float initTime
) : LevelEvent(initTime) {
	this->animation = animation;
	this->animatedValueType = animatedValueType;
	this->shapeGroupID = shapeGroupID;
	this->shapeNum = shapeNum;
	this->valueNum = valueNum;
	this->type = LevelEventType::SHAPE_ANIMATION;
}

ShapeAnimationEvent* ShapeAnimationEvent::create(
	Animation animation,
	AnimatedValueType animatedValueType,
	int shapeGroupID,
	int shapeNum,
	int vertexNum,
	int valueNum,
	float initTime
) {
	return new ShapeAnimationEvent(
		animation,
		animatedValueType,
		shapeGroupID,
		shapeNum,
		vertexNum,
		valueNum,
		initTime
	);
}

ShapeAnimationEvent* ShapeAnimationEvent::create(
	Animation animation,
	AnimatedValueType animatedValueType,
	int shapeGroupID,
	int shapeNum,
	int valueNum,
	float initTime
) {
	return new ShapeAnimationEvent(
		animation,
		animatedValueType,
		shapeGroupID,
		shapeNum,
		valueNum,
		initTime
	);
}

ShapeAnimationEvent* ShapeAnimationEvent::create(
	char* byteArray,
	float initTime
) {
	unsigned int offset = 0;
	AnimatedValueType animatedValueType;
	int shapeGroupID, shapeNum, vertexNum, valueNum;
	writeFromByteArray((char*)&animatedValueType, byteArray, offset, sizeof(animatedValueType));
	writeFromByteArray((char*)&shapeGroupID, byteArray, offset, sizeof(shapeGroupID));
	writeFromByteArray((char*)&shapeNum, byteArray, offset, sizeof(shapeNum));
	writeFromByteArray((char*)&vertexNum, byteArray, offset, sizeof(vertexNum));
	writeFromByteArray((char*)&valueNum, byteArray, offset, sizeof(valueNum));
	return new ShapeAnimationEvent(
		Animation(byteArray, offset),
		animatedValueType,
		shapeGroupID,
		shapeNum,
		vertexNum,
		valueNum,
		initTime
	);
}

void ShapeAnimationEvent::start() {
	Shape* shape = &(*shapeGroups[shapeGroupID]).getShapesPointer()[shapeNum];
	if (animatedValueType != AnimatedValueType::SHAPE_COLOR) { //UUUuuu kostyl
		float* target;
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
	else {
		unsigned int shapeVertexCount = shape->getVertexCount();
		float** targets = new float* [shapeVertexCount];
		for (unsigned int i = 0; i < shapeVertexCount; i++) {
			targets[i] = &shape->getVertexColorsPointer()[valueNum + i * 4];
		}
		AnimationController::add(AnimationTask(animation, targets, shapeVertexCount));
	}

}

std::vector<char> ShapeAnimationEvent::getByteArray() {
	std::vector<char> animationArray = animation.getByteArray();
	unsigned int byteArraySize =
		static_cast<unsigned int>(
			animationArray.size() +
			sizeof(animatedValueType) +
			sizeof(shapeGroupID) +
			sizeof(shapeNum) +
			sizeof(vertexNum) +
			sizeof(valueNum));

	std::vector<char> byteArray(byteArraySize);

	unsigned int offset = 0;

	writeToByteArray(byteArray, (char*)&animatedValueType, offset, sizeof(animatedValueType));
	writeToByteArray(byteArray, (char*)&shapeGroupID, offset, sizeof(shapeGroupID));
	writeToByteArray(byteArray, (char*)&shapeNum, offset, sizeof(shapeNum));
	writeToByteArray(byteArray, (char*)&vertexNum, offset, sizeof(vertexNum));
	writeToByteArray(byteArray, (char*)&valueNum, offset, sizeof(valueNum));
	writeToByteArray(byteArray, animationArray, offset);

	return byteArray;
}