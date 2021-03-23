#include "Engine.h"
#include "EventController.h"
#include "AnimationController.h"
#include "Shape.h"
#include "LevelEvent.h"
#include "Graphics.h"

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

void Engine::init() {
	Graphics::init();
	PlayerBindingEvent::player = &player;

	EventController::level = std::vector<LevelEvent*>();
	AnimationController::setTimePointer(&frameTime);
	window = Graphics::getWindow();
	EventController::currentTime = &currentTime;

	
	uint vertexCount = 4;
	float* vertexCoords = new float[] {0.f, 0.f, 0.f, 1.f, 1.f, 0.f, 1.f, 1.f};
	float* vertexColors = new float[] {0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 1.f};
	uint* vertexIDs = new uint[]{ 0, 1, 2, 1, 2, 3 };
	uint EBOsize = 6;

	Shape* shape = new Shape(vertexCount, vertexCoords, vertexColors, EBOsize, vertexIDs);

	uint keyCount = 2;

	float* stateKeys = new float[] { 1.f, 0.0f };
	float* timeKeys = new float[] {0, 3e3f};

	Animation* animation = new Animation(keyCount, timeKeys, stateKeys);

	EventController::level.push_back(new ShapeSpawnEvent(shape, 0, 0));
	EventController::level.push_back(new PlayerBindingEvent(0, 0));
	EventController::level.push_back(new ShapeAnimationEvent(animation, AnimatedValueType::COLOR, 0, 0, 0, 3, 3e3f));
	EventController::level.push_back(new ShapeDestructionEvent(0, 4e3f));
	
	LevelEvent::dynamicShapes = new std::list<Shape*>::iterator[5];

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
	Graphics::draw();
}

bool Engine::running() {
	return Graphics::running();
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
