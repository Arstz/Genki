#pragma once
#include <SFML/Graphics.hpp>

class RenderHandler
{
	sf::ConvexShape* shapes;
	float offsetX;
	float offsetY;
	float scale;
	int shapeCount;

	sf::RenderWindow* mainWindow;

	void render();
};
