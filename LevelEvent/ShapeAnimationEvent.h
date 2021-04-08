#pragma once
#include "LevelEvent.h"

class ShapeAnimationEvent : public LevelEvent {
	Animation animation;
	AnimatedValueType animatedValueType;
	int shapeGroupID;
	int shapeNum;
	int vertexNum;
	int valueNum;

	ShapeAnimationEvent(
		Animation animation,
		AnimatedValueType animatedValueType,
		int shapeGroupID,
		int shapeNum,
		int vertexNum,
		int valueNum,
		float initTime
	);
public:

	static ShapeAnimationEvent* create(
		Animation animation,
		AnimatedValueType animatedValueType,
		int shapeGroupID,
		int shapeNum,
		int vertexNum,
		int valueNum,
		float initTime
	);
	static ShapeAnimationEvent* create(
		char* byteArray,
		float initTime
	);

	void start() override;
	std::vector<char> getByteArray() override;
};