#include "PlayerBindingEvent.h"
#include "..\AnimationController.h"
#include "..\ShapeController.h"
#include "..\ByteArray.h"

Player* PlayerBindingEvent::player = nullptr;

PlayerBindingEvent::PlayerBindingEvent(int shapeGroupID, float initTime): LevelEvent(initTime) {
	this->shapeGroupID = shapeGroupID;
	this->type = LevelEventType::PLAYER_BINDING;
}
PlayerBindingEvent* PlayerBindingEvent::create(int shapeGroupID, float initTime) {
	return new PlayerBindingEvent(shapeGroupID, initTime);
}

PlayerBindingEvent* PlayerBindingEvent::create(
	char* byteArray,
	float initTime
) {
	unsigned int offset = 0;
	int shapeGroupID;
	writeFromByteArray((char*)&shapeGroupID, byteArray, offset, sizeof(shapeGroupID));
	return new PlayerBindingEvent(shapeGroupID, initTime);
}

void PlayerBindingEvent::start() {
	player->setTarget(
		(*(shapeGroups[shapeGroupID])).getPositionXpointer(),
		(*(shapeGroups[shapeGroupID])).getPositionYpointer()
	);
}

std::vector<char> PlayerBindingEvent::getByteArray() {
	unsigned int byteArraySize = sizeof(shapeGroupID);
	std::vector<char> byteArray(byteArraySize);

	unsigned int offset = 0;

	writeToByteArray(byteArray, (char*)&shapeGroupID, offset, sizeof(shapeGroupID));

	return byteArray;
}