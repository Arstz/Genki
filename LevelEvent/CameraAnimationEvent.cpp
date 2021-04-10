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
	char* byteArray,
	float initTime
) {
	unsigned int offset = 0;
	uint valueNum;
	writeFromByteArray((char*)&valueNum, byteArray, offset, sizeof(valueNum));
	return new CameraAnimationEvent(Animation(byteArray, offset), valueNum, initTime);
}

void CameraAnimationEvent::start() {
	AnimationController::add(AnimationTask(animation, ShapeController::getCameraValuePointer(valueNum)));
}

std::vector<char> CameraAnimationEvent::getByteArray() {
	std::vector<char> animationArray = animation.getByteArray();
	unsigned int byteArraySize = static_cast<unsigned int>(animationArray.size()) + sizeof(valueNum);

	std::vector<char> byteArray(byteArraySize);

	unsigned int offset = 0;

	writeToByteArray(byteArray, (char*)&valueNum, offset, sizeof(valueNum));
	writeToByteArray(byteArray, animationArray, offset);

	return byteArray;
}