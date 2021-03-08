#pragma once
class LevelEvent
{
public:
	float initTime = 0;

	virtual void end() {

	}

	virtual void init() {

	}

	virtual void update() {

	}
};

class CameraEvent : public LevelEvent {
	float* offset;

	 CameraEvent(float &offset) {
		 this->offset = &offset;
	 }
};

