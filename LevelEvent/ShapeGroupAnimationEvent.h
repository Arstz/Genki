#pragma once
#include "LevelEvent.h"

class ShapeGroupAnimationEvent : public LevelEvent {
	Animation animation;
	AnimatedValueType animatedValueType;
	int shapeGroupID;

	ShapeGroupAnimationEvent(
		Animation animation,
		AnimatedValueType animatedValueType,
		int shapeGroupID,
		float initTime
	);
public:

	static ShapeGroupAnimationEvent* create(
		Animation animation,
		AnimatedValueType animatedValueType,
		int shapeGroupID,
		float initTime
	);
	static ShapeGroupAnimationEvent* create(
		char* byteArray,
		float initTime
	);

	void start() override;
	std::vector<char> getByteArray() override;
};