#include "LevelEvent.h"

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
	ByteArray* byteArray,
	float initTime
) {
	AnimatedValueType animatedValueType;
	int shapeGroupID, shapeNum, vertexNum, valueNum;
	byteArray->read(animatedValueType);
	byteArray->read(shapeGroupID);
	byteArray->read(shapeNum);
	byteArray->read(vertexNum);
	byteArray->read(valueNum);
	return new ShapeAnimationEvent(
		Animation(byteArray),
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
		delete[] targets;
		targets = nullptr;
	}
}

ByteArray ShapeAnimationEvent::getByteArray() {
	ByteArray animationArray = animation.getByteArray();
	unsigned int byteArraySize =
		static_cast<unsigned int>(
			animationArray.getSize() +
			sizeof(animatedValueType) +
			sizeof(shapeGroupID) +
			sizeof(shapeNum) +
			sizeof(vertexNum) +
			sizeof(valueNum));

	ByteArray byteArray(byteArraySize);

	byteArray.add(animatedValueType);
	byteArray.add(shapeGroupID);
	byteArray.add(shapeNum);
	byteArray.add(vertexNum);
	byteArray.add(valueNum);
	byteArray.add(animationArray);

	return byteArray;
}