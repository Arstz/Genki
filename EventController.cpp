#include "EventController.h"
#include "LevelEvent.h"
#include <iostream>
#include <fstream>

std::vector<LevelEvent*> EventController::level;
int EventController::currentEvent = 0;
float* EventController::currentTime = nullptr;

void EventController::updateActiveEventList() 
{
	while (currentEvent < level.size() && level[currentEvent]->getInitTime() < *currentTime) {
		level[currentEvent]->start();
		currentEvent++;
	}
}

void EventController::loadLevel(std::string path) {
	std::ifstream fin;
	fin.open("raid_na_derevene.lvl", std::ifstream::binary);
	size_t size = 0;
	fin.read((char*)(&size), sizeof(size_t));
	for (int i = 0; i < size; i++)
	{
		size_t type = level[i]->getType();
		fin.read((char*)(&type), sizeof(LevelEventType));
		switch (type)
		{
		case LevelEventType::EMPTY:
			break;
		case LevelEventType::BACKGROUND_COLOR_ANIMATION:
			break;
		case LevelEventType::CAMERA_ANIMATION:
			break;
		case LevelEventType::SHAPE_SPAWN:
			break;
		case LevelEventType::SHAPE_DESTRUCTION:
			break;
		case LevelEventType::SHAPE_ANIMATION:
			break;
		case LevelEventType::PLAYER_BINDING:
			break;
		}

	}
	
}

void EventController::saveLevel(std::string path, std::vector<LevelEvent*> level) {
	std::ofstream fout;
	fout.open("raid_na_derevene.lvl", std::ifstream::binary);
	size_t size = level.size();
	fout.write((char*)(&size), sizeof(size_t));
	for (int i = 0; i < size; i++)
	{
		LevelEventType type = level[i]->getType();
		fout.write((char*)(&type), sizeof(LevelEventType));
		switch (type)
		{
		case LevelEventType::EMPTY:

			break;
		case LevelEventType::BACKGROUND_COLOR_ANIMATION:
			break;
		case LevelEventType::CAMERA_ANIMATION:
			break;
		case LevelEventType::SHAPE_SPAWN:
			break;
		case LevelEventType::SHAPE_DESTRUCTION:
			break;
		case LevelEventType::SHAPE_ANIMATION:
			break;
		case LevelEventType::PLAYER_BINDING:
			break;
		}

	}
	
}