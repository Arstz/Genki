#pragma once
#include "LevelEvent.h"

class PlayerBindingEvent : public LevelEvent {
	PlayerBindingEvent(int shapeGroupID, float initTime);
	int shapeGroupID;
public:
	static Player* player;
	static PlayerBindingEvent* create(
		int shapeGroupID,
		float initTime
	);
	static PlayerBindingEvent* create(
		char* byteArray,
		float initTime
	);
	void start() override;
	std::vector<char> getByteArray() override;
};