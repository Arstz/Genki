#pragma once
#include "EventController.h"
#include "Player.h"
#include "Shape.h"

#include <chrono>
#include <fstream>
#include <list>
#include <iostream>

class Engine
{

private:

	void initVars();
	void initGameObjects();
	void pollEvents();
	void setMoveDirection();

//	sf::Vector2i lastDir;

	float currentTime;

	std::chrono::system_clock::time_point start;

	Player player;
	EventController eventController;

public:
	Engine();
	virtual ~Engine();
	
	void update();
	void render();

	bool running();
};

