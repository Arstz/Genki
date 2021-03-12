#pragma once
#include <SFML/Graphics.hpp>
#include "EventController.h"
#include "RenderHandler.h"
#include "Player.h"

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

	sf::Vector2i lastDir;

	float currentTime;

	sf::RenderWindow* mainWindow;
	sf::Event eventHandler;

	std::list<AnimationTask> animationTasks;
	std::list<sf::VertexArray> shapes;
	std::list<sf::VertexArray>::iterator* dynamicShapes;

	Player player;
	EventController eventController;
	RenderHandler renderHandler;

public:
	Engine();
	virtual ~Engine();
	
	void update();
	void render();

	const bool running() const;
};

