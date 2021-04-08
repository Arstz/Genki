#pragma once
#include <list>
#include "..\Animation.h"
#include "..\AnimationTask.h"
#include "..\Player.h"
#include "..\Shape.h"
#include "..\ShapeGroup.h"
#include <fstream>
#include <vector>

class EventController;

enum class LevelEventType {
	EMPTY,
	BACKGROUND_COLOR_ANIMATION, //cherez 5 let sdelaem
	CAMERA_ANIMATION,
	SHAPE_SPAWN,
	SHAPE_GROUP_SPAWN,
	SHAPE_GROUP_DESTRUCTION,
	SHAPE_ANIMATION,
	SHAPE_GROUP_ANIMATION,
	PLAYER_BINDING,
};

enum class AnimatedValueType {
	VERTEX_POSITION,
	VERTEX_COLOR,
	ALPHA_CHANNEL,
	POSITION_X,
	POSITION_Y,
};

class LevelEvent {
	friend EventController;
protected:
	float initTime;
	LevelEventType type;
	LevelEvent();
	virtual ~LevelEvent();
	LevelEvent(float initTime);

public:
	static std::list<ShapeGroup>::iterator* shapeGroups;
	virtual void write(std::ofstream& fout);
	virtual void start();
	virtual std::vector<char> getByteArray();
	static void destroy();
	float getInitTime();

	LevelEventType getType();
};









