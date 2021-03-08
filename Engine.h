#pragma once
#include <SFML/Graphics.hpp>
#include "EventController.h"
#include "RenderHandler.h"

#include <chrono>
#include <fstream>
#include <tuple>
#include <list>


class Engine
{

private:

	void initVars();
	void initGameObjects();
	void initWindow();
	void pollEvents();
	void setMoveDirection();
	void movePlayer();
	void stopPlayer();

	float playerPosX;
	float playerPosY;

	int lastDirX;
	int lastDirY;

	int moveDirectionX;
	int moveDirectionY;

	float currentTime;

	sf::RenderWindow* mainWindow;
	sf::Event eventHandler;

	sf::ConvexShape* player;
	std::list<sf::ConvexShape> shapes;
	EventController eventController;
	RenderHandler renderHandler;

public:
	Engine();
	virtual ~Engine();
	
	void update();
	void render();

	const bool running() const;
};

