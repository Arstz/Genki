#pragma once
#include <list>
#include "Animation.h"
#include "AnimationTask.h"
#include "Player.h"
#include "Shape.h"
#include <fstream>

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

enum AnimatedValueType {
	VERTEX,
	COLOR,
};

class LevelEvent
{
	friend EventController;
protected:
	float initTime;
	LevelEventType type;

public:
	static std::list<Shape*>::iterator* dynamicShapes;
	virtual void write(std::ofstream& fout);
	virtual void start();
	float getInitTime();

	LevelEvent();
	LevelEvent(float initTime);

	LevelEventType getType();
};

class CameraAnimationEvent : public LevelEvent {

	Animation* animation;
	uint valueNum;
public:
	CameraAnimationEvent();
	CameraAnimationEvent(
		Animation* animation, 
		uint valueNum,
		float initTime
	);
	void write(std::ofstream& fout) override;
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
	void write(std::ofstream& fout) override;
	void start() override;
};

class ShapeDestructionEvent : public LevelEvent { //opasniy pizdets
	int shapeID;
public:
	ShapeDestructionEvent();
	ShapeDestructionEvent(int shapeID, float initTime);
	void write(std::ofstream& fout) override;
	void start() override;
};

class ShapeAnimationEvent : public LevelEvent {
	Animation* animation;
	AnimatedValueType animatedValueType;
	int shapeID;
	int AnimatedValueID;
	int vertexNum;
	int channelNum;
public:
	ShapeAnimationEvent();
	ShapeAnimationEvent(
		Animation* animation,
		AnimatedValueType animatedValueType,
		int AnimatedValueID,
		int shapeID,
		int vertexNum,
		int channelNum,
		float initTime
	);
	void write(std::ofstream& fout) override;
	void start() override;
};

class PlayerBindingEvent : public LevelEvent {
public:
	static Player* player;
	int shapeID;

	PlayerBindingEvent();
	PlayerBindingEvent(int shapeID, float initTime);
	void write(std::ofstream& fout) override;
	void start() override;
};

class BackgroundColorAnimationEvent : public LevelEvent {
public:
	uint animatedValueID;
	Animation* animation;

	BackgroundColorAnimationEvent();
	BackgroundColorAnimationEvent(uint animatedValueID, Animation* animation, float initTime);
	void write(std::ofstream& fout) override;
	void start() override;
};