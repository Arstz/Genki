#include "LevelEvent.h"

BackgroundColorAnimationEvent::BackgroundColorAnimationEvent(
	Animation animation, 
	uint valueNum, 
	float initTime
): LevelEvent(initTime) {
	this->type = LevelEventType::BACKGROUND_COLOR_ANIMATION;
	this->animation = animation;
	this->valueNum = valueNum;
}

BackgroundColorAnimationEvent* BackgroundColorAnimationEvent::create(
	Animation animation,
	uint valueNum,
	float initTime
) {
	return new BackgroundColorAnimationEvent(animation, valueNum, initTime);
}

BackgroundColorAnimationEvent* BackgroundColorAnimationEvent::create(
	ByteArray* byteArray,
	float initTime
) {
	uint valueNum;
	byteArray->read(valueNum);
	return new BackgroundColorAnimationEvent(Animation(byteArray), valueNum, initTime);
}

void BackgroundColorAnimationEvent::start() {
	AnimationController::add(AnimationTask(animation, Window::getBackgroundColorValuePointer(valueNum)));
}

ByteArray BackgroundColorAnimationEvent::getByteArray() {
	ByteArray animationArray = animation.getByteArray();
	ByteArray byteArray(animationArray.getSize() + sizeof(valueNum));

	byteArray.add(valueNum);
	byteArray.add(animationArray);

	return byteArray;
}