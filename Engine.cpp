#include "Engine.h"
#include "EventController.h"
#include "AnimationController.h"
#include "Shape.h"
#include "ShapeGroup.h"
#include "LevelEvent.h"
#include "Window.h"
#include "ShapeController.h"

#define AAAA (static_cast <float> (rand()) / static_cast <float> (RAND_MAX))
#define BBBB (2.f*static_cast <float> (rand()) / static_cast <float> (RAND_MAX) - 1)/2

#define IS_RIGHT_KEY_PRESSED (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
#define IS_LEFT_KEY_PRESSED (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
#define IS_UP_KEY_PRESSED (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
#define IS_DOWN_KEY_PRESSED (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)

float Engine::currentTime = 0;
float Engine::frameTime = 0;
std::chrono::system_clock::time_point Engine::start = std::chrono::system_clock::now();
Player Engine::player = Player();
GLFWwindow* Engine::window = nullptr;

void Engine::terminate() {
	glfwTerminate();
}

void Engine::init() {
	Window::init();
	ShapeController::init();

	PlayerBindingEvent::player = &player;

	AnimationController::setTimePointer(&frameTime);
	window = Window::getWindow();
	EventController::currentTime = &currentTime;
	
	uint vertexCount = 4;
	uint EBOsize = 6;
	uint keyCount = 2;

	float vertexCoords[] = {0.f, 0.f, 0.f, 1.f, 1.f, 0.f, 1.f, 1.f};
	float vertexColors[] = {0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 1.f};
	float vertexColors2[] = {0.f, 0.f, 0.f, 0.0f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 1.f};
	uint* vertexIDs = new uint[]{ 0, 1, 2, 1, 2, 3 };


	float cds1[] = {-0.75f, 0.f, -0.75f, 1.f, 0.25f, 0.f, 0.25, 1.f};
	float cls[] = {0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 1.f};

	float cds2[] = {-0.25f, 0.f, -0.25f, 1.f, 0.75f, 0.f, 0.75, 1.f};

	Shape shps[] = {
		Shape(4, cds1, cls, 6, vertexIDs, 0.5, 0, 0, 0),
		Shape(4, cds2, cls, 6, vertexIDs, 0.5, 0, 0, 0),
	};

	ShapeGroup a(2, 0, shps, nullptr, 1, 0, 0, 0);


	Shape* shape = new Shape(vertexCount, vertexCoords, vertexColors, EBOsize, vertexIDs, 0.5, 10, 5, 0);
	Shape* shape2 = new Shape(vertexCount, vertexCoords, vertexColors2, EBOsize, vertexIDs, 1, 1, 1, 0);


	EventController::level.push_back(new ShapeSpawnEvent(*shape, 0, 0));
	EventController::level.push_back(new ShapeSpawnEvent(*shape, 1, 0));
	EventController::level.push_back(new ShapeSpawnEvent(*shape2, 2, 0));
	EventController::level.push_back(new ShapeGroupSpawnEvent(a, 0, 0));
	EventController::level.push_back(new PlayerBindingEvent(0, 0));

//	EventController::level.push_back(new ShapeDestructionEvent(0, 10e3f));
	
	LevelEvent::shapeGroups = new std::list<ShapeGroup*>::iterator[4];

//	EventController::saveLevel("a", EventController::level);
//	EventController::loadLevel("a");
}

void Engine::pollEvents() {
	glfwPollEvents();
}

void Engine::update() {
	pollEvents();
	pollKeyEvents();
	auto end = std::chrono::system_clock::now();
	frameTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() - currentTime;
	currentTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	EventController::update();
	AnimationController::update();
}

void Engine::render() {
	ShapeController::draw();
	Window::clear();
	
}

bool Engine::running() {
	return Window::running();
}

void Engine::pollKeyEvents() {
	if (IS_RIGHT_KEY_PRESSED && IS_LEFT_KEY_PRESSED) {
		if (player.lastDirectionX == 1) {
			player.move(-1.f, 0.f);
		} else player.move(1.f, 0.f);
	}
	else if (IS_LEFT_KEY_PRESSED) {
		player.move(-1.f, 0.f);
		player.lastDirectionX = -1;
	}
	else if (IS_RIGHT_KEY_PRESSED) {
		player.move(1.f, 0.f);
		player.lastDirectionX = 1;
	}
	if (IS_DOWN_KEY_PRESSED && IS_UP_KEY_PRESSED) {
		if (player.lastDirectionY == 1) {
			player.move(0.f, -1.f);
		}
		else player.move(0.f, 1.f);
	}
	else if (IS_DOWN_KEY_PRESSED) {
		player.move(0.f, -1.f);
		player.lastDirectionY = -1;
	}
	else if (IS_UP_KEY_PRESSED) {
		player.move(0.f, 1.f);
		player.lastDirectionY = 1;
	}
}
