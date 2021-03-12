#include "Engine.h"
#include "LevelEvent.h"

//Variables
void Engine::initVars() {	
	this->eventHandler = sf::Event();
	start = std::chrono::system_clock::now();
}

//Game Objects
void Engine::initGameObjects() {
	std::list<AnimationTask> animationTasks;
	std::list<sf::VertexArray> shapes;
	std::list<sf::VertexArray>::iterator* dynamicShapes = new std::list<sf::VertexArray>::iterator[3];    //;) MAXIM3 :)
	LevelEvent::animationTasks = &animationTasks;
	LevelEvent::shapes = &shapes;
	LevelEvent::dynamicShapes = dynamicShapes; //kak krytoi)
	PlayerBindingEvent::player = &player;
}

//Main Window
void Engine::initWindow(){	
	mainWindow = new sf::RenderWindow(sf::VideoMode(1000, 1000), "Sample", sf::Style::Titlebar | sf::Style::Close);
	mainWindow->setFramerateLimit(170);
}

//Construct
Engine::Engine() {
	
	LevelEvent* level = new LevelEvent[2];

	sf::VertexArray shape(sf::Triangles, 3);

	shape[0].position = sf::Vector2f(0.f, 0.f);
	shape[1].position = sf::Vector2f(0.f, 30.f);
	shape[2].position = sf::Vector2f(30.f, 30.f);

	shape[0].color = sf::Color(255, 255, 255, 255);
	shape[1].color = sf::Color(255, 255, 255, 255);
	shape[2].color = sf::Color(255, 255, 255, 255);

	level[0] = ShapeSpawnEvent(shape, 0);

	initVars();
	initWindow();
	initGameObjects();
	this->renderHandler = RenderHandler(&shapes,mainWindow);
	this->player = Player();
	this->eventController = EventController(&currentTime, level);
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
}

void Engine::update(){
	pollEvents();
	auto end = std::chrono::system_clock::now();
	currentTime = (float)(end - start).count();
	std::cout << currentTime;
	setMoveDirection();
}

void Engine::render(){
	mainWindow->clear();
	renderHandler.renderShapes();
	mainWindow->display();
}

const bool Engine::running() const{
	return mainWindow->isOpen();
}
