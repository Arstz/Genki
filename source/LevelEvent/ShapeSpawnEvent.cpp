#include "LevelEvent.h"

ShapeSpawnEvent* ShapeSpawnEvent::create(Shape shape, int shapeGroupID, int targetShapeGroupID, float initTime) {
	return new ShapeSpawnEvent(shape, shapeGroupID, targetShapeGroupID, initTime);
}

ShapeSpawnEvent* ShapeSpawnEvent::create(
	ByteArray* byteArray,
	float initTime
) {
	int shapeGroupID, targetShapeGroupID;
	*byteArray >> shapeGroupID >> targetShapeGroupID;
	return new ShapeSpawnEvent(Shape(byteArray), shapeGroupID, targetShapeGroupID, initTime);
}

ShapeSpawnEvent::ShapeSpawnEvent(
	Shape shape,
	int shapeGroupID,
	int targetShapeGroupID,
	float initTime
): LevelEvent(initTime) {
	this->shapeGroupID = shapeGroupID;
	this->targetShapeGroupID = targetShapeGroupID;
	this->shape = shape;
	this->type = LevelEventType::SHAPE_SPAWN;
}

void ShapeSpawnEvent::start() {
	if (targetShapeGroupID) shapeGroups[shapeGroupID] = ShapeController::addShapeGroup(ShapeGroup(shape), shapeGroups[targetShapeGroupID]);
	else shapeGroups[shapeGroupID] = ShapeController::addShapeGroup(ShapeGroup(shape));
}

ByteArray ShapeSpawnEvent::getByteArray() {
	ByteArray shapeArray = shape.getByteArray();
	ByteArray byteArray(
		shapeArray.getSize() +
		sizeof(shapeGroupID) +
		sizeof(targetShapeGroupID)
	);
	byteArray << shapeGroupID << targetShapeGroupID << shapeArray;
	return byteArray;
}