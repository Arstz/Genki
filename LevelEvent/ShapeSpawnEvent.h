#pragma once
#include "LevelEvent.h"

class ShapeSpawnEvent : public LevelEvent {
	int shapeGroupID;
	int targetShapeGroupID;
	Shape shape;
	ShapeSpawnEvent(
		Shape shape,
		int shapeGroupID,
		int targetShapeGroupID,
		float initTime
	);
public:
	static ShapeSpawnEvent* create(
		Shape shape,
		int shapeGroupID,
		int targetShapeGroupID,
		float initTime
	);
	static ShapeSpawnEvent* create(
		char* byteArray,
		float initTime
	);
	void start() override;

	std::vector<char> getByteArray() override;
};