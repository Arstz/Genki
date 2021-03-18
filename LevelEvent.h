#pragma once
#include <list>
#include "Animation.h"
#include "AnimationTask.h"
#include "Player.h"
#include "Shape.h"

class EventController;

enum LevelEventType {
	EMPTY,
	BACKGROUND_COLOR_ANIMATION, //cherez 100 let sdelaem
	CAMERA_ANIMATION,
	SHAPE_SPAWN,
	SHAPE_DESTRUCTION,
	SHAPE_ANIMATION,
	PLAYER_BINDING,
};

class LevelEvent
{
	friend EventController;
protected:
	enum AnimatedValueType {
		VERTEX,
		COLOR,
	};

	float initTime;
	LevelEventType type;

	static std::list<Shape*>::iterator* dynamicShapes;
public:
	virtual void start();
	float getInitTime();

	LevelEvent();
	LevelEvent(float initTime);

	LevelEventType getType();
};

class CameraAnimationEvent : public LevelEvent {

	Animation animation;
	uint valueNum;
public:
	CameraAnimationEvent();
	CameraAnimationEvent(
		Animation animation, 
		uint valueNum,
		float initTime
	);

	void start() override;
};

class ShapeSpawnEvent : public LevelEvent {
	int shapeID;
	Shape* shape;
public:
	ShapeSpawnEvent();
	ShapeSpawnEvent(
		Shape* shape, 
		int shapeID, 
		float initTime
	);

	void start() override;
};

class ShapeDestructionEvent : public LevelEvent {
	int shapeID;
public:
	ShapeDestructionEvent();
	ShapeDestructionEvent(int shapeID, float initTime);

	void start() override;
};

class ShapeAnimationEvent : public LevelEvent {
	Animation animation;
	AnimatedValueType animatedValueType;
	int AnimatedValueID;
	int shapeID;
	int vertexNum;
	int channelNum;
public:
	ShapeAnimationEvent();
	ShapeAnimationEvent(
		Animation animation,
		AnimatedValueType animatedValueType,
		int AnimatedValueID,
		int shapeID,
		int vertexNum,
		int channelNum
	);

	void start() override;
};

class PlayerBindingEvent : public LevelEvent {
public:
	static Player* player;
	int shapeID;

	PlayerBindingEvent();
	PlayerBindingEvent(int shapeID, float initTime);

	void start() override;
};