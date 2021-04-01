#pragma once
#include <list>
#include "Animation.h"
#include "AnimationTask.h"
#include "Player.h"
#include "Shape.h"
#include "ShapeGroup.h"
#include <fstream>

class EventController;

enum LevelEventType {
	EMPTY,
	BACKGROUND_COLOR_ANIMATION, //cherez 5 let sdelaem
	CAMERA_ANIMATION,
	SHAPE_SPAWN,
	SHAPE_DESTRUCTION,
	SHAPE_ANIMATION,
	PLAYER_BINDING,
};

enum AnimatedValueType {
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
	LevelEvent(float initTime);

public:
	static std::list<ShapeGroup>::iterator* shapeGroups;
	virtual void write(std::ofstream& fout);
	virtual void start();
	float getInitTime();

	LevelEventType getType();
};

class CameraAnimationEvent : public LevelEvent {
	Animation animation;
	uint valueNum;

	CameraAnimationEvent();
	CameraAnimationEvent(
		Animation animation,
		uint valueNum,
		float initTime
	);

public:
	static CameraAnimationEvent* create(
		Animation animation,
		uint valueNum,
		float initTime
	);
	
	void start() override;
//	void write(std::ofstream& fout) override;
};

class ShapeSpawnEvent : public LevelEvent {
	int shapeGroupID;
	int targetShapeGroupID;
	Shape shape;
	ShapeSpawnEvent(
		Shape shape,
		int shapeGroupID,
		int targetShapeGroupID,
		float initTime
	);
	ShapeSpawnEvent();
public:
	static ShapeSpawnEvent* create(
		Shape shape,
		int shapeGroupID,
		int targetShapeGroupID,
		float initTime
	);
	void start() override;

//	void write(std::ofstream& fout) override;
};

class ShapeGroupSpawnEvent : public LevelEvent {
	int shapeGroupID;
	int targetShapeGroupID;
	ShapeGroup shapeGroup;
	ShapeGroupSpawnEvent();
	ShapeGroupSpawnEvent(
		ShapeGroup shapeGroup,
		int shapeGroupID,
		int targetShapeGroupID,
		float initTime
	);
public:
	static ShapeGroupSpawnEvent* create(
		ShapeGroup shapeGroup,
		int shapeGroupID,
		int targetShapeGroupID,
		float initTime
	);
	//	void write(std::ofstream& fout) override;
	void start() override;
};

class ShapeGroupDestructionEvent : public LevelEvent { //opasniy pizdets
	int shapeGroupID;
	ShapeGroupDestructionEvent();
	ShapeGroupDestructionEvent(int shapeGroupID, float initTime);
public:

	static ShapeGroupDestructionEvent* create(int shapeGroupID, float initTime);

	void start() override;
//	void write(std::ofstream& fout) override;
};

class ShapeAnimationEvent : public LevelEvent {
	Animation animation;
	AnimatedValueType animatedValueType;
	int shapeGroupID;
	int animatedValueID;
	int shapeNum;
	int vertexNum;
	int valueNum;

	ShapeAnimationEvent();
	ShapeAnimationEvent(
		Animation animation,
		AnimatedValueType animatedValueType,
		int shapeGroupID,
		int animatedValueID,
		int shapeNum,
		int vertexNum,
		int valueNum,
		float initTime
	);
public:

	static ShapeAnimationEvent* create(
		Animation animation,
		AnimatedValueType animatedValueType,
		int shapeGroupID,
		int animatedValueID,
		int shapeNum,
		int vertexNum,
		int valueNum,
		float initTime
	);

	void start() override;
//	void write(std::ofstream& fout) override;
};

class ShapeGroupAnimationEvent : public LevelEvent {
	Animation animation;
	AnimatedValueType animatedValueType;
	int shapeGroupID;


	ShapeGroupAnimationEvent();
	ShapeGroupAnimationEvent(
		Animation animation,
		AnimatedValueType animatedValueType,
		int shapeGroupID,
		float initTime
	);
public:

	static ShapeGroupAnimationEvent* create(
		Animation animation,
		AnimatedValueType animatedValueType,
		int shapeGroupID,
		float initTime
	);

	void start() override;
	//	void write(std::ofstream& fout) override;
};

class PlayerBindingEvent : public LevelEvent {
	PlayerBindingEvent();
	PlayerBindingEvent(int shapeGroupID, float initTime);
	int shapeGroupID;
public:
	static Player* player;

	static PlayerBindingEvent* create(int shapeGroupID, float initTime);

//	void write(std::ofstream& fout) override;
	void start() override;
};

class BackgroundColorAnimationEvent : public LevelEvent {
	uint animatedValueID;
	Animation animation;

	BackgroundColorAnimationEvent();
	BackgroundColorAnimationEvent(uint animatedValueID, Animation animation, float initTime);
public:
	static BackgroundColorAnimationEvent* create(
		uint animatedValueID,
		Animation animation,
		float initTime
	);
//	void write(std::ofstream& fout) override;
	void start() override;
};
