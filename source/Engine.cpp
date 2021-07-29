#include "Engine.h"
#include "EventController.h"
#include "AnimationController.h"
#include "Shape.h"
#include "ShapeGroup.h"
#include "LevelEvent\LevelEvent.h"
#include "Window.h"
#include "ShapeController.h"
#include "GUIcanvas.h"
#include "Vector2f.h"
#include "GUI.h"
#include "Text.h"

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
GLFWwindow* Engine::window = nullptr;
ShapeController* Engine::levelShapeController = nullptr;
Player Engine::player = Player();

void Engine::destroy()
{
	AnimationController::destroy();
	levelShapeController->destroy();
	EventController::destroy();
}

void Engine::terminate() {
	glfwTerminate();
}

void Engine::init() {

	Window::init(1920, 1080);
	window = Window::getWindow();
	GUIcanvas::setWindow();


	ShapeController::setWindow(window);
	ShapeController::initShader();
	GUIcanvas::init();
	levelShapeController = new ShapeController();


	start = std::chrono::system_clock::now();
	player = Player();
	PlayerBindingEvent::player = &player;

	AnimationController::setTimePointer(&frameTime);

	EventController::currentTime = &currentTime;

	LevelEvent::setShapeGroupsSize(10);
	LevelEvent::setShapeController(levelShapeController);

	EventController::loadLevel("a");

//	EventController::saveLevel("a", EventController::level);

	GUIcanvas::addSex(Vector2f(0, 0), Vector2f(1, 3));
	GUIcanvas::addSex(Vector2f(-10, -10), Vector2f(5, 5));
	float* x = new float(0);
	float* y = new float(0);
	bool* z = new bool(0);
	*z = false;
	GUIcanvas::addSlider(Vector2f(-7, -3), Vector2f(0, 10), x, y, Vector2f(200, 200), Vector2f(500, 500));
	GUIcanvas::addSlider(Vector2f(-5, -5), Vector2f(8, 0), x, y, Vector2f(200, 200), Vector2f(500, 500));
	GUIcanvas::addCheckBox(Vector2f(7, 7), Vector2f(1, 1), z);
	Text::setScale(Vector2f(0.3, 0.3));
	GUIobject(Text::makeText("AMOGUS", Vector2f(-5, -4)), GUIcanvas::shapeController);
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
	GUIcanvas::update();
	EventController::update();
	AnimationController::update();

}

void Engine::render() {
	Window::clear();
	levelShapeController->draw();
	GUIcanvas::draw();
	
	
	glfwSwapBuffers(window);
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
