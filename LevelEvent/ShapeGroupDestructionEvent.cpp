#include "ShapeGroupDestructionEvent.h"
#include "..\AnimationController.h"
#include "..\ShapeController.h"
#include "..\ByteArray.h"

ShapeGroupDestructionEvent::ShapeGroupDestructionEvent(int shapeGroupID, float initTime): LevelEvent(initTime) {
	this->shapeGroupID = shapeGroupID;
	this->type = LevelEventType::SHAPE_GROUP_DESTRUCTION;
}

ShapeGroupDestructionEvent* ShapeGroupDestructionEvent::create(int shapeGroupID, float initTime) {
	return new ShapeGroupDestructionEvent(shapeGroupID, initTime);
}

ShapeGroupDestructionEvent* ShapeGroupDestructionEvent::create(
	char* byteArray,
	float initTime
) {
	unsigned int offset = 0;
	int shapeGroupID;
	writeFromByteArray((char*)&shapeGroupID, byteArray, offset, sizeof(shapeGroupID));
	return new ShapeGroupDestructionEvent(shapeGroupID, initTime);
}

void ShapeGroupDestructionEvent::start() {
	ShapeController::removeShapeGroup(shapeGroups[shapeGroupID]);
}

std::vector<char> ShapeGroupDestructionEvent::getByteArray() {
	unsigned int byteArraySize = sizeof(shapeGroupID);
	std::vector<char> byteArray(byteArraySize);

	unsigned int offset = 0;

	writeToByteArray(byteArray, (char*)&shapeGroupID, offset, sizeof(shapeGroupID));

	return byteArray;
}