#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "Animation.h"
#include "AnimationTask.h"

enum LevelEventType {
	CAMERA_ANIMATION,
	SHAPE_SPAWN,
	SHAPE_DESTRUCTION,
	SHAPE_ANIMATION,
	PLAYER_BINDING,
};

enum AnimatedValueType {
	CAMERA_SCALE,
	CAMERA_OFFSET_X,
	CAMERA_OFFSET_Y,

	SHAPE_VERTEX_X,
	SHAPE_VERTEX_Y,
	SHAPE_COLOR_R,
	SHAPE_COLOR_G,
	SHAPE_COLOR_B,
	SHAPE_COLOR_A,
};

class LevelEvent
{
public:
	float initTime;

	virtual void start();
	virtual LevelEvent* load();

	LevelEvent();
	LevelEvent(float initTime);

};
class CameraAnimationEvent : public LevelEvent {
public:
	static std::list<AnimationTask>* animationTasks;
	Animation animation;
	AnimatedValueType animatedValueType;

	void start() override;
};

class ShapeSpawnEvent : public LevelEvent {
public:
	static std::list<sf::VertexArray>* shapes;
	static std::list<sf::VertexArray>::iterator* dynamicShapes;
	int shapeID;
	sf::VertexArray shape;
	ShapeSpawnEvent();
	ShapeSpawnEvent(sf::VertexArray shape, float initTime);

	void start() override;
};

class ShapeDestructionEvent : public LevelEvent {
public:
	static std::list<sf::VertexArray>::iterator* dynamicShapes;
	int shapeID;

	void start() override;
};

class ShapeAnimationEvent : public LevelEvent {
public:
	static std::list<AnimationTask>* animationTasks;
	static std::list<sf::VertexArray>::iterator* dynamicShapes;
	Animation animation;
	AnimatedValueType animatedValueType;

	void start() override;
};

class PlayerBindingEvent : public LevelEvent {
public:
	static std::list<sf::VertexArray>::iterator* dynamicShapes;
	int shapeID;

	void start() override;
};