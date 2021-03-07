#pragma once
class LevelEvent
{
	float initTime = 0;

	virtual void endEvent() {

	}

	virtual void initEvent() {

	}
};

class CameraEvent : public LevelEvent {
	float* offset;

	 CameraEvent(float &offset) {
		 this->offset = &offset;
	 }
};

