#include "LevelEvent.h"

CameraAnimationEvent::CameraAnimationEvent(
	Animation animation,
	uint valueNum,
	float initTime
): LevelEvent::LevelEvent(initTime) {
	this->animation = animation;
	this->valueNum = valueNum;
	this->type = LevelEventType::CAMERA_ANIMATION;
}

CameraAnimationEvent* CameraAnimationEvent::create(Animation animation, uint valueNum, float initTime) {
	return new CameraAnimationEvent(animation, valueNum, initTime);
}

CameraAnimationEvent* CameraAnimationEvent::create(
	ByteArray* byteArray,
	float initTime
) {
	uint valueNum;
	*byteArray >> valueNum;
	return new CameraAnimationEvent(Animation(byteArray), valueNum, initTime);
}

void CameraAnimationEvent::start() {
	AnimationController::add(AnimationTask(animation, shapeController->getCameraValuePointer(valueNum)));
}

ByteArray CameraAnimationEvent::getByteArray() {
	ByteArray animationArray = animation.getByteArray();
	ByteArray byteArray(animationArray.getSize() + sizeof(valueNum));
	byteArray << valueNum << animationArray;
	return byteArray;
}
