#include "Engine.h"
#include "EventController.h"
#include "AnimationController.h"
#include "Shape.h"
#include "ShapeGroup.h"
#include "LevelEvent\LevelEvent.h"
#include "Window.h"
#include "ShapeController.h"

#include "crtdbg.h"
#include "..\include\CRTDBG\mydbgnew.h"
#ifdef _DEBUG
#define new MYDEBUG_NEW
#endif

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

void Engine::destroy()
{
	AnimationController::destroy();
	ShapeController::destroy();
	EventController::destroy();
}

void Engine::terminate() {
	ShapeController::terminate();
	delete[] LevelEvent::shapeGroups;

	glfwTerminate();
}

void Engine::init() {
	Window::init();
	window = Window::getWindow();
	ShapeController::init();

	PlayerBindingEvent::player = &player;

	AnimationController::setTimePointer(&frameTime);
	
	EventController::currentTime = &currentTime;
	
	LevelEvent::shapeGroups = new std::list<ShapeGroup>::iterator[10];

	EventController::loadLevel("a");

//	EventController::saveLevel("a", EventController::level);
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
