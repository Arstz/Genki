#pragma once
#include <list>
#include "..\Animation.h"
#include "..\AnimationTask.h"
#include "..\Player.h"
#include "..\Shape.h"
#include "..\ShapeGroup.h"
#include "..\AnimationController.h"
#include "..\ShapeController.h"
#include "..\ByteArray.h"
#include <fstream>
#include <vector>

class EventController;

enum class LevelEventType {
	EMPTY,
	BACKGROUND_COLOR_ANIMATION,
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
	SHAPE_COLOR
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
	virtual void start();
	virtual ByteArray getByteArray();
	float getInitTime();

	LevelEventType getType();
};


class BackgroundColorAnimationEvent : public LevelEvent {
	Animation animation;
	uint valueNum;

	BackgroundColorAnimationEvent(Animation animation, uint valueNum, float initTime);
public:
	static BackgroundColorAnimationEvent* create(
		Animation animation,
		uint valueNum,
		float initTime
	);
	static BackgroundColorAnimationEvent* create(
		ByteArray* byteArray,
		float initTime
	);
	void start() override;
	ByteArray getByteArray() override;
};


class CameraAnimationEvent : public LevelEvent {
	Animation animation;
	uint valueNum;

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

	static CameraAnimationEvent* create(
		ByteArray* byteArray,
		float initTime
	);

	void start() override;
	ByteArray getByteArray() override;
};


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
		ByteArray* byteArray,
		float initTime
	);
	void start() override;
	ByteArray getByteArray() override;
};


class ShapeAnimationEvent : public LevelEvent {
	Animation animation;
	AnimatedValueType animatedValueType;
	int shapeGroupID;
	int shapeNum;
	int vertexNum;
	int valueNum;
	ShapeAnimationEvent(
		Animation animation,
		AnimatedValueType animatedValueType,
		int shapeGroupID,
		int shapeNum,
		int vertexNum,
		int valueNum,
		float initTime
	);
	ShapeAnimationEvent(
		Animation animation,
		AnimatedValueType animatedValueType,
		int shapeGroupID,
		int shapeNum,
		int valueNum,
		float initTime
	);
public:

	static ShapeAnimationEvent* create(
		Animation animation,
		AnimatedValueType animatedValueType,
		int shapeGroupID,
		int shapeNum,
		int vertexNum,
		int valueNum,
		float initTime
	);
	static ShapeAnimationEvent* create(
		Animation animation,
		AnimatedValueType animatedValueType,
		int shapeGroupID,
		int shapeNum,
		int valueNum,
		float initTime
	);
	static ShapeAnimationEvent* create(
		ByteArray* byteArray,
		float initTime
	);

	void start() override;
	ByteArray getByteArray() override;
};


class ShapeGroupAnimationEvent : public LevelEvent {
	Animation animation;
	AnimatedValueType animatedValueType;
	int shapeGroupID;

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
	static ShapeGroupAnimationEvent* create(
		ByteArray* byteArray,
		float initTime
	);

	void start() override;
	ByteArray getByteArray() override;
};


class ShapeGroupDestructionEvent : public LevelEvent { //opasniy pizdets
	int shapeGroupID;
	ShapeGroupDestructionEvent(int shapeGroupID, float initTime);
public:

	static ShapeGroupDestructionEvent* create(
		int shapeGroupID,
		float initTime
	);

	static ShapeGroupDestructionEvent* create(
		ByteArray* byteArray,
		float initTime
	);

	void start() override;
	ByteArray getByteArray() override;
};


class ShapeGroupSpawnEvent : public LevelEvent {
	ShapeGroup shapeGroup;
	int shapeGroupID;
	int targetShapeGroupID;

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
	static ShapeGroupSpawnEvent* create(
		ByteArray* byteArray,
		float initTime
	);
	ByteArray getByteArray() override;
	void start() override;
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
public:
	static ShapeSpawnEvent* create(
		Shape shape,
		int shapeGroupID,
		int targetShapeGroupID,
		float initTime
	);
	static ShapeSpawnEvent* create(
		ByteArray* byteArray,
		float initTime
	);
	void start() override;

	ByteArray getByteArray() override;
};
