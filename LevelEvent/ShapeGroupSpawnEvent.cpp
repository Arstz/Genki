#include "ShapeGroupSpawnEvent.h"
#include "..\AnimationController.h"
#include "..\ShapeController.h"
#include "..\ByteArray.h"

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
	char* byteArray,
	float initTime
) {
	unsigned int offset = 0;
	int shapeGroupID, targetShapeGroupID;
	writeFromByteArray((char*)&shapeGroupID, byteArray, offset, sizeof(shapeGroupID));
	writeFromByteArray((char*)&targetShapeGroupID, byteArray, offset, sizeof(targetShapeGroupID));
	return new ShapeGroupSpawnEvent(ShapeGroup(byteArray, offset), shapeGroupID, targetShapeGroupID, initTime);
}

std::vector<char> ShapeGroupSpawnEvent::getByteArray() {
	std::vector<char> shapeGroupArray = shapeGroup.getByteArray();
	unsigned int byteArraySize =
		static_cast<unsigned int>(
			shapeGroupArray.size() +
			sizeof(shapeGroupID) +
			sizeof(targetShapeGroupID));

	std::vector<char> byteArray(byteArraySize);

	unsigned int offset = 0;

	writeToByteArray(byteArray, (char*)&shapeGroupID, offset, sizeof(shapeGroupID));
	writeToByteArray(byteArray, (char*)&targetShapeGroupID, offset, sizeof(targetShapeGroupID));
	writeToByteArray(byteArray, shapeGroupArray, offset);

	return byteArray;
}

void ShapeGroupSpawnEvent::start() {
	if (targetShapeGroupID) shapeGroups[shapeGroupID] = ShapeController::addShapeGroup(shapeGroup, shapeGroups[targetShapeGroupID]);
	else shapeGroups[shapeGroupID] = ShapeController::addShapeGroup(shapeGroup);
}