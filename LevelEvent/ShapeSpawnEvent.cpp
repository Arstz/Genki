#include "ShapeSpawnEvent.h"
#include "..\AnimationController.h"
#include "..\ShapeController.h"
#include "..\ByteArray.h"

ShapeSpawnEvent* ShapeSpawnEvent::create(Shape shape, int shapeGroupID, int targetShapeGroupID, float initTime) {
	return new ShapeSpawnEvent(shape, shapeGroupID, targetShapeGroupID, initTime);
}

ShapeSpawnEvent* ShapeSpawnEvent::create(
	char* byteArray,
	float initTime
) {
	unsigned int offset = 0;
	int shapeGroupID, targetShapeGroupID;
	writeFromByteArray((char*)&shapeGroupID, byteArray, offset, sizeof(shapeGroupID));
	writeFromByteArray((char*)&targetShapeGroupID, byteArray, offset, sizeof(targetShapeGroupID));
	return new ShapeSpawnEvent(Shape(byteArray, offset), shapeGroupID, targetShapeGroupID, initTime);
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

std::vector<char> ShapeSpawnEvent::getByteArray() {
	std::vector<char> shapeArray = shape.getByteArray();
	unsigned int byteArraySize =
		static_cast<unsigned int>(
			shapeArray.size() +
			sizeof(shapeGroupID) +
			sizeof(targetShapeGroupID));

	std::vector<char> byteArray(byteArraySize);

	unsigned int offset = 0;

	writeToByteArray(byteArray, (char*)&shapeGroupID, offset, sizeof(shapeGroupID));
	writeToByteArray(byteArray, (char*)&targetShapeGroupID, offset, sizeof(targetShapeGroupID));
	writeToByteArray(byteArray, shapeArray, offset);

	return byteArray;
}