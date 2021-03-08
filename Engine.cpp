#include "Engine.h"

//Variables
void Engine::initVars(){
	this->mainWindow = nullptr;
	this->eventHandler = sf::Event();
}

//Game Objects
void Engine::initGameObjects(){
	this->player.setSize(sf::Vector2f(15.f, 15.f));
	this->player.setFillColor(sf::Color::Yellow);
	this->player.setPosition(sf::Vector2f(500.f, 500.f));
}

//Main Window
void Engine::initWindow(){	
	this->mainWindow = new sf::RenderWindow(sf::VideoMode(1000, 1000), "Sample", sf::Style::Titlebar | sf::Style::Close);
	this->mainWindow->setFramerateLimit(170);
}

//Construct
Engine::Engine() {
	this->initVars();
	this->initWindow();
	this->initGameObjects();
}

//Destruct
Engine::~Engine() {
	delete this->mainWindow;
}

void Engine::pollEvents(){
	while (this->mainWindow->pollEvent(this->eventHandler)) {

		switch (this->eventHandler.type){

		case sf::Event::Closed: this->mainWindow->close(); 
			break;			
		default:
			break;
		}
	}
}

void Engine::setMoveDirection(){
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		if (this->lastDirX == 1) {
			this->moveDirectionX = -1;
		}
		else {
			this->moveDirectionX = 1;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		this->moveDirectionX = -1;
		this->lastDirX = -1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		this->moveDirectionX = 1;
		this->lastDirX = 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		if (this->lastDirY == 1) {
			this->moveDirectionY = -1;
		}
		else {
			this->moveDirectionY = 1;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		this->moveDirectionY = -1;
		this->lastDirY = -1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		this->moveDirectionY = 1;
		this->lastDirY = 1;
	}
}

void Engine::movePlayer() {
	this->playerPosX += this->moveDirectionX;
	this->playerPosY += this->moveDirectionY;
}

void Engine::stopPlayer()
{
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		this->moveDirectionX = 0;
	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		moveDirectionY = 0;
	}
}

void Engine::update(){
	this->pollEvents();
	this->stopPlayer();
	this->setMoveDirection();
	this->movePlayer();
	this->player.setPosition(sf::Vector2f(playerPosX, playerPosY));
}

void Engine::render(){
	this->mainWindow->clear();
	this->mainWindow->draw(this->player);
	this->mainWindow->display();
}

const bool Engine::running() const{
	return this->mainWindow->isOpen();
}
