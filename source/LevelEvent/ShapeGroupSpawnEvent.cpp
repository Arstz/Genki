#include "LevelEvent.h"

ShapeGroupSpawnEvent::ShapeGroupSpawnEvent(
	ShapeGroup shapeGroup,
	int shapeGroupID,
	int targetShapeGroupID,
	float initTime
): LevelEvent(initTime) {
	this->shapeGroupID = shapeGroupID;
	this->shapeGroup = shapeGroup;
	this->type = LevelEventType::SHAPE_GROUP_SPAWN;
}

ShapeGroupSpawnEvent* ShapeGroupSpawnEvent::create(ShapeGroup shapeGroup, int shapeGroupID, int targetShapeGroupID, float initTime) {
	return new ShapeGroupSpawnEvent(shapeGroup, shapeGroupID, targetShapeGroupID, initTime);
}

ShapeGroupSpawnEvent* ShapeGroupSpawnEvent::create(
	ByteArray* byteArray,
	float initTime
) {
	int shapeGroupID, targetShapeGroupID;
	*byteArray >> shapeGroupID >> targetShapeGroupID;
	return new ShapeGroupSpawnEvent(ShapeGroup(byteArray), shapeGroupID, targetShapeGroupID, initTime);
}

ByteArray ShapeGroupSpawnEvent::getByteArray() {
	ByteArray shapeGroupArray = shapeGroup.getByteArray();
	ByteArray byteArray(
		shapeGroupArray.getSize() +
		sizeof(shapeGroupID) +
		sizeof(targetShapeGroupID)
	);
	byteArray << shapeGroupID << targetShapeGroupID << shapeGroupArray;
	return byteArray;
}

void ShapeGroupSpawnEvent::start() {
	if (targetShapeGroupID) shapeGroups[shapeGroupID] = ShapeController::addShapeGroup(shapeGroup, shapeGroups[targetShapeGroupID]);
	else shapeGroups[shapeGroupID] = ShapeController::addShapeGroup(shapeGroup);
}