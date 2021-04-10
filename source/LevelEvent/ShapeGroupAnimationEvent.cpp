#include "LevelEvent.h"

ShapeGroupAnimationEvent::ShapeGroupAnimationEvent(
	Animation animation,
	AnimatedValueType animatedValueType,
	int shapeGroupID,
	float initTime
): LevelEvent(initTime) {
	this->animation = animation;
	this->animatedValueType = animatedValueType;
	this->shapeGroupID = shapeGroupID;
	this->type = LevelEventType::SHAPE_GROUP_ANIMATION;
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

ShapeGroupAnimationEvent* ShapeGroupAnimationEvent::create(
	char* byteArray,
	float initTime
) {
	unsigned int offset = 0;
	AnimatedValueType animatedValueType;
	int shapeGroupID;
	writeFromByteArray((char*)&animatedValueType, byteArray, offset, sizeof(animatedValueType));
	writeFromByteArray((char*)&shapeGroupID, byteArray, offset, sizeof(shapeGroupID));
	return new ShapeGroupAnimationEvent(
		Animation(byteArray, offset),
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

std::vector<char> ShapeGroupAnimationEvent::getByteArray() {
	std::vector<char> animationArray = animation.getByteArray();
	unsigned int byteArraySize =
		static_cast<unsigned int>(
			animationArray.size() +
			sizeof(animatedValueType) +
			sizeof(shapeGroupID));

	std::vector<char> byteArray(byteArraySize);

	unsigned int offset = 0;

	writeToByteArray(byteArray, (char*)&animatedValueType, offset, sizeof(animatedValueType));
	writeToByteArray(byteArray, (char*)&shapeGroupID, offset, sizeof(shapeGroupID));
	writeToByteArray(byteArray, animationArray, offset);

	return byteArray;
}