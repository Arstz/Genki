#pragma once
#include "LevelEvent.h"

class ShapeGroupDestructionEvent : public LevelEvent { //opasniy pizdets
	int shapeGroupID;
	ShapeGroupDestructionEvent(int shapeGroupID, float initTime);
public:

	static ShapeGroupDestructionEvent* create(
		int shapeGroupID,
		float initTime
	);

	static ShapeGroupDestructionEvent* create(
		char* byteArray,
		float initTime
	);

	void start() override;
	std::vector<char> getByteArray() override;
};