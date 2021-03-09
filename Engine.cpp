#include "Engine.h"

//Variables
void Engine::initVars(){	
	this->eventHandler = sf::Event();
}

//Game Objects
void Engine::initGameObjects(){
	shapes = new std::list<sf::VertexArray*>;
	player = new sf::VertexArray(sf::Triangles, 3);



	(*player)[0].position = sf::Vector2f(0.f, 0.f);
	(*player)[1].position = sf::Vector2f(0.f, 15.f);
	(*player)[2].position = sf::Vector2f(15.f, 15.f);


	(*player)[0].color = sf::Color(255, 255, 255, 255);
	(*player)[1].color = sf::Color(255, 255, 255, 255);
	(*player)[2].color = sf::Color(255, 255, 255, 255);

	shapes->push_back(player);
}

//Main Window
void Engine::initWindow(){	
	mainWindow = new sf::RenderWindow(sf::VideoMode(1000, 1000), "Sample", sf::Style::Titlebar | sf::Style::Close);
	mainWindow->setFramerateLimit(170);
}

//Construct
Engine::Engine() {
	this->eventController = EventController(currentTime);	
	initVars();
	initWindow();
	initGameObjects();
	this->renderHandler = RenderHandler(shapes,mainWindow);
}

//Destruct
Engine::~Engine() {
	delete this->mainWindow;
}

void Engine::pollEvents(){
	while (mainWindow->pollEvent(eventHandler)) {

		switch (eventHandler.type){

		case sf::Event::Closed: mainWindow->close(); 
			break;			
		default:
			break;
		}
	}
}

void Engine::setMoveDirection(){
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		if (lastDirX == 1) {
			moveDirectionX = -1;
		}
		else {
			moveDirectionX = 1;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		moveDirectionX = -1;
		lastDirX = -1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		moveDirectionX = 1;
		lastDirX = 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		if (lastDirY == 1) {
			moveDirectionY = -1;
		}
		else {
			moveDirectionY = 1;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		moveDirectionY = -1;
		lastDirY = -1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		moveDirectionY = 1;
		lastDirY = 1;
	}
}

void Engine::movePlayer() {
	playerPosX += moveDirectionX;
	playerPosY += moveDirectionY;
}

void Engine::stopPlayer()
{
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		moveDirectionX = 0;
	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		moveDirectionY = 0;
	}
}

void Engine::update(){
	pollEvents();
	stopPlayer();
	setMoveDirection();
	movePlayer();

	(*player)[0].position.x = playerPosX + 0.f;
	(*player)[0].position.y = playerPosY + 0.f;

	(*player)[1].position.x = playerPosX + 0.f;
	(*player)[1].position.y = playerPosY + 15.f;

	(*player)[2].position.x = playerPosX + 15.f;
	(*player)[2].position.y = playerPosY + 15.f;

}

void Engine::render(){
	mainWindow->clear();
	renderHandler.renderShapes();
	mainWindow->display();
}

const bool Engine::running() const{
	return mainWindow->isOpen();
}
