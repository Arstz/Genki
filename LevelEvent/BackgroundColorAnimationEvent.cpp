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
	char* byteArray,
	float initTime
) {
	unsigned int offset = 0;
	uint valueNum;
	writeFromByteArray((char*)&valueNum, byteArray, offset, sizeof(valueNum));
	return new BackgroundColorAnimationEvent(Animation(byteArray, offset), valueNum, initTime);
}

void BackgroundColorAnimationEvent::start() {
	AnimationController::add(AnimationTask(animation, Window::getBackgroundColorValuePointer(valueNum)));
}

std::vector<char> BackgroundColorAnimationEvent::getByteArray() {
	std::vector<char> animationArray = animation.getByteArray();
	unsigned int byteArraySize = static_cast<unsigned int>(animationArray.size() + sizeof(valueNum));

	std::vector<char> byteArray(byteArraySize);

	unsigned int offset = 0;

	writeToByteArray(byteArray, (char*)&valueNum, offset, sizeof(valueNum));
	writeToByteArray(byteArray, animationArray, offset);

	return byteArray;
}