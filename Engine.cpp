#include "Engine.h"
#include "LevelEvent.h"
#include "Graphics.h"
#include <vector>

//Variables
void Engine::initVars() {	
	start = std::chrono::system_clock::now();
	Graphics::init();
}

//Game Objects
void Engine::initGameObjects() {
	this->player = Player();
	PlayerBindingEvent::player = &player;
	std::vector<LevelEvent*> level;
	this->eventController = EventController(&currentTime, level.size(), level);
}


//Construct
Engine::Engine() {
	initVars();
	initGameObjects();
}

//Destruct
Engine::~Engine() {

}

void Engine::pollEvents() {
	glfwPollEvents();
}

void Engine::setMoveDirection(){
	/*
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		if (lastDir.x == 1) {
			player.move(sf::Vector2f(-1.f, 0.f));
		}
		else {
			player.move(sf::Vector2f(1.f, 0.f));
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		player.move(sf::Vector2f(-1.f, 0.f));
		lastDir.x = -1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		player.move(sf::Vector2f(1.f, 0.f));
		lastDir.x = 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		if (lastDir.y == 1) {
			player.move(sf::Vector2f(0.f, -1.f));
		}
		else {
			player.move(sf::Vector2f(0.f, 1.f));
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		player.move(sf::Vector2f(0.f, -1.f));
		lastDir.y = -1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		player.move(sf::Vector2f(0.f, 1.f));
		lastDir.y = 1;
	}
	*/
}

void Engine::update(){
	pollEvents();
	auto end = std::chrono::system_clock::now();
	currentTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	setMoveDirection();
	eventController.updateActiveEventList();
}

void Engine::render(){

}

bool Engine::running() {
	return Graphics::running();
}
