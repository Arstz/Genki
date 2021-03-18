#pragma once
#include "LevelEvent.h"
#include <list>
#include <vector>
#include <string>

class EventController
{
public:
	static std::vector<LevelEvent*> level;
	static int currentEvent;
	static float* currentTime;

	static void updateEvents();
	static void updateActiveEventList();
	static void loadLevel(std::string path);
	static void saveLevel(std::string path, std::vector<LevelEvent*> level);
};