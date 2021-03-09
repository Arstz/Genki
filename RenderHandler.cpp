#include "RenderHandler.h"
#include <iostream>

RenderHandler::RenderHandler(){}

RenderHandler::RenderHandler(std::list<sf::ConvexShape*>* &shapes, sf::RenderWindow* &mainWindow){
	this->shapes = shapes;
	this->mainWindow = mainWindow;
}

void RenderHandler::renderShapes()
{
	for (auto &shape : *shapes) {		
		mainWindow->draw(*shape);
	}
}
