#pragma once
#include <SFML/Graphics.hpp>
#include <list>

class RenderHandler
{
	
	float offsetX;
	float offsetY;
	float scale;
	int shapeCount;
	std::list<sf::ConvexShape>* shapes;
	sf::ConvexShape* player;

	sf::RenderWindow* mainWindow;
public:
	RenderHandler();	
	RenderHandler(std::list<sf::ConvexShape>* &shapes, sf::RenderWindow* &mainWindow, sf::ConvexShape* &player);

	void renderPlayer();
	void renderShapes();
};
