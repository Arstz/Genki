#include "RenderHandler.h"
#include <iostream>

RenderHandler::RenderHandler(){}

RenderHandler::RenderHandler(std::list<sf::ConvexShape>* &shapes, sf::RenderWindow* &mainWindow, sf::ConvexShape*& player){
	this->shapes = shapes;
	this->mainWindow = mainWindow;
	this->player = player;
}

void RenderHandler::renderPlayer()
{
	mainWindow->draw(*player);
}

void RenderHandler::renderShapes()
{
	for (auto shape : *shapes) {		
		mainWindow->draw(shape);
	}
}
