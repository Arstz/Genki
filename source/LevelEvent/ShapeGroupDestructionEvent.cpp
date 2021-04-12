#include "LevelEvent.h"

ShapeGroupDestructionEvent::ShapeGroupDestructionEvent(int shapeGroupID, float initTime): LevelEvent(initTime) {
	this->shapeGroupID = shapeGroupID;
	this->type = LevelEventType::SHAPE_GROUP_DESTRUCTION;
}

ShapeGroupDestructionEvent* ShapeGroupDestructionEvent::create(int shapeGroupID, float initTime) {
	return new ShapeGroupDestructionEvent(shapeGroupID, initTime);
}

ShapeGroupDestructionEvent* ShapeGroupDestructionEvent::create(
	ByteArray* byteArray,
	float initTime
) {
	int shapeGroupID;
	*byteArray >> shapeGroupID;
	return new ShapeGroupDestructionEvent(shapeGroupID, initTime);
}

void ShapeGroupDestructionEvent::start() {
	ShapeController::removeShapeGroup(shapeGroups[shapeGroupID]);
}

ByteArray ShapeGroupDestructionEvent::getByteArray() {
	ByteArray byteArray(sizeof(shapeGroupID));
	byteArray >> shapeGroupID;
	return byteArray;
}