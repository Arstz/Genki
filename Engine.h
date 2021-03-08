#pragma once
#include <SFML/Graphics.hpp>

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

	sf::RenderWindow* mainWindow;
	sf::Event eventHandler;

	sf::RectangleShape player;

public:
	Engine();
	virtual ~Engine();
	
	void update();
	void render();

	const bool running() const;
};

