#include "LevelEvent.h"
#include <SFML/Graphics.hpp>

std::list<sf::VertexArray>* ShapeSpawnEvent::shapes = nullptr;

LevelEvent* LevelEvent::load()
{

}

void LevelEvent::start()
{

}

void CameraAnimationEvent::start()
{

}

void ShapeSpawnEvent::start()
{
	shapes->push_front(shape);
}

void ShapeDestructionEvent::start()
{

}

void ShapeAnimationEvent::start()
{

}

void PlayerBindingEvent::start()
{

}


LevelEvent::LevelEvent() {

}

LevelEvent::LevelEvent(float initTime) {
	this->initTime = initTime;
}

ShapeSpawnEvent::ShapeSpawnEvent()
{

}



ShapeSpawnEvent::ShapeSpawnEvent(sf::VertexArray shape, float initTime) : LevelEvent(initTime) {
	this->shape = shape;
}
