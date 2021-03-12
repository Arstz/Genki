#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "Animation.h"
#include "AnimationTask.h"
#include "Player.h"

enum LevelEventType {
	BACKGROUND_COLOR_ANIMATION, //cherez 200 let sdelaem
	CAMERA_ANIMATION,
	SHAPE_SPAWN,
	SHAPE_DESTRUCTION,
	SHAPE_ANIMATION,
	PLAYER_BINDING,
};

class LevelEvent
{
protected:
	enum AnimatedValueType {
		CAMERA_SCALE,
		CAMERA_OFFSET_X,
		CAMERA_OFFSET_Y,

		SHAPE_VERTEX_X,
		SHAPE_VERTEX_Y,
		COLOR_R,
		COLOR_G,
		COLOR_B,
		COLOR_A,
	};

	float initTime;	
public:
	static std::list<AnimationTask>* animationTasks;
	static std::list<sf::VertexArray>* shapes;
	static std::list<sf::VertexArray>::iterator* dynamicShapes;

	virtual void start();
	virtual LevelEvent* load();
	float getInitTime();

	LevelEventType type;

	LevelEvent();
	LevelEvent(LevelEventType type, float initTime);

};

class CameraAnimationEvent : public LevelEvent {
public:
	Animation animation;
	AnimatedValueType animatedValueType;

	void start() override;
};

class ShapeSpawnEvent : public LevelEvent {
public:

	int shapeID;
	sf::VertexArray shape;
	ShapeSpawnEvent();
	ShapeSpawnEvent(sf::VertexArray shape, int shapeID, LevelEventType type, float initTime);

	void start() override;
};

class ShapeDestructionEvent : public LevelEvent {
public:
	int shapeID;

	void start() override;
};

class ShapeAnimationEvent : public LevelEvent {
public:
	Animation animation;
	AnimatedValueType animatedValueType;
	int AnimatedValueID;
	int shapeID;

	void start() override;
};

class PlayerBindingEvent : public LevelEvent {
public:
	static Player* player;
	int shapeID;
	PlayerBindingEvent(int shapeID, LevelEventType type, float initTime);

	void start() override;
};
