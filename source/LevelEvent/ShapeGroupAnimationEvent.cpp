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
	ByteArray* byteArray,
	float initTime
) {
	AnimatedValueType animatedValueType;
	int shapeGroupID;
	*byteArray >> animatedValueType >> shapeGroupID;
	return new ShapeGroupAnimationEvent(
		Animation(byteArray),
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

ByteArray ShapeGroupAnimationEvent::getByteArray() {
	ByteArray animationArray = animation.getByteArray();
	ByteArray byteArray(
		animationArray.getSize() +
		sizeof(animatedValueType) +
		sizeof(shapeGroupID)
	);
	byteArray << animatedValueType << shapeGroupID << animationArray;
	return byteArray;
}