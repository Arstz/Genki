#include "LevelEvent.h"
#include <SFML/Graphics.hpp>
#define FUCKING_VERTEX (*(dynamicShapes[shapeID]))[AnimatedValueID]


//LevelEvent


std::list<AnimationTask>* LevelEvent::animationTasks = nullptr;
std::list<sf::VertexArray>* LevelEvent::shapes = nullptr;
std::list<sf::VertexArray>::iterator* LevelEvent::dynamicShapes = nullptr;

LevelEvent* LevelEvent::load()
{

}

void LevelEvent::start()
{

}

float LevelEvent::getInitTime() {
	return initTime;
}

LevelEvent::LevelEvent() {

}

LevelEvent::LevelEvent(float initTime) {
	this->initTime = initTime;
}

//CameraAnimationEvent

void CameraAnimationEvent::start()
{
	/*
	float* target;
	switch (animatedValueType)
	{
	case CAMERA_SCALE:
		target = ;
		break;
	case CAMERA_OFFSET_X:
		target = ;
		break;
	case CAMERA_OFFSET_Y:
		target = ;
		break;
	default:
		throw "WRONG ANIMATED VALUE TYPE";
		break;
	}
	
	animationTasks->push_back(AnimationTask(animation, *target));
	*/
}

//ShapeSpawnEvent

void ShapeSpawnEvent::start()
{
	shapes->push_front(shape);
	dynamicShapes[shapeID] = shapes->begin();
}

ShapeSpawnEvent::ShapeSpawnEvent() {}

ShapeSpawnEvent::ShapeSpawnEvent(sf::VertexArray shape, float initTime) : LevelEvent(initTime) {
	this->shape = shape;
}

//ShapeDestructionEvent

void ShapeDestructionEvent::start()
{
	shapes->erase(dynamicShapes[shapeID]);
}

//ShapeAnimationEvent
void ShapeAnimationEvent::start()
{
	float* target;
	switch(animatedValueType)
	{
	case SHAPE_VERTEX_X:
		target = &FUCKING_VERTEX.position.x;
		break;
	case SHAPE_VERTEX_Y:
		target = &FUCKING_VERTEX.position.y;
		break;
	/* AHAHA tsvet budet tolko v openGL potomu chto tut color - eto int :D
	case COLOR_R:
		target = &FUCKING_VERTEX.color.r;
		break;
	*/
	default:
		throw "WRONG ANIMATED VALUE TYPE";
		break;
	}
	animationTasks->push_back(AnimationTask(animation, target));
}

//PlayerBindingEvent

void PlayerBindingEvent::start()
{

}
