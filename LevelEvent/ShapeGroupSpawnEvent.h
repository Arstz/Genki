#pragma once
#include "LevelEvent.h"

class ShapeGroupSpawnEvent : public LevelEvent {
	ShapeGroup shapeGroup;
	int shapeGroupID;
	int targetShapeGroupID;

	ShapeGroupSpawnEvent(
		ShapeGroup shapeGroup,
		int shapeGroupID,
		int targetShapeGroupID,
		float initTime
	);
public:
	static ShapeGroupSpawnEvent* create(
		ShapeGroup shapeGroup,
		int shapeGroupID,
		int targetShapeGroupID,
		float initTime
	);
	static ShapeGroupSpawnEvent* create(
		char* byteArray,
		float initTime
	);
	std::vector<char> getByteArray() override;
	void start() override;
};