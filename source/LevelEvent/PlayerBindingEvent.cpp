#include "LevelEvent.h"

Player* PlayerBindingEvent::player = nullptr;

PlayerBindingEvent::PlayerBindingEvent(int shapeGroupID, float initTime): LevelEvent(initTime) {
	this->shapeGroupID = shapeGroupID;
	this->type = LevelEventType::PLAYER_BINDING;
}
PlayerBindingEvent* PlayerBindingEvent::create(int shapeGroupID, float initTime) {
	return new PlayerBindingEvent(shapeGroupID, initTime);
}

PlayerBindingEvent* PlayerBindingEvent::create(
	ByteArray* byteArray,
	float initTime
) {
	int shapeGroupID;
	*byteArray >> shapeGroupID;
	return new PlayerBindingEvent(shapeGroupID, initTime);
}

void PlayerBindingEvent::start() {
	player->setTarget(
		(*(shapeGroups[shapeGroupID])).getPositionXpointer(),
		(*(shapeGroups[shapeGroupID])).getPositionYpointer()
	);
}

ByteArray PlayerBindingEvent::getByteArray() {
	ByteArray byteArray(sizeof(shapeGroupID));
	byteArray << shapeGroupID;
	return byteArray;
}