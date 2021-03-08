#include "RenderHandler.h"

RenderHandler::RenderHandler(){}

RenderHandler::RenderHandler(std::list<sf::ConvexShape> shapes){
	this->shapes = shapes;
}

void RenderHandler::render()
{
	for (auto &shape : shapes) {
		mainWindow->draw(shape);
	}
}
