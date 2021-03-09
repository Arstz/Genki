#pragma once
#include <SFML/Graphics.hpp>
#include <list>

class RenderHandler
{
	
	float offsetX;
	float offsetY;
	float scale;
	int shapeCount;
	std::list<sf::VertexArray*>* shapes;
	sf::VertexArray* player;

	sf::RenderWindow* mainWindow;
public:
	RenderHandler();	
	RenderHandler(std::list<sf::VertexArray*>* &shapes, sf::RenderWindow* &mainWindow);

	void renderShapes();
};
