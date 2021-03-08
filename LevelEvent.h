#pragma once
enum LevelEventType {
	CAMERA_EVENT,
	GEOMETRY_EVENT,
	AUDIO_EVENT,
};

class LevelEvent
{
public:
	float initTime = 0;
	LevelEventType type;

	virtual void end() {

	}

	virtual void start() {

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

