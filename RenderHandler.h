#pragma once
#include <SFML/Graphics.hpp>
#include <list>

class RenderHandler
{
	
	float offsetX;
	float offsetY;
	float scale;
	int shapeCount;

	sf::RenderWindow* mainWindow;
public:
	RenderHandler();
	std::list<sf::ConvexShape> shapes;
	RenderHandler(std::list<sf::ConvexShape> shapes);

	void render();
};
