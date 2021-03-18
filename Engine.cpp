#include "Engine.h"
#include "EventController.h"
#include "Shape.h"
#include "LevelEvent.h"
#include "Graphics.h"
#define AAAA (static_cast <float> (rand()) / static_cast <float> (RAND_MAX))
#define BBBB (2.f*static_cast <float> (rand()) / static_cast <float> (RAND_MAX) - 1)/2

float Engine::currentTime = 0;
std::chrono::system_clock::time_point Engine::start = std::chrono::system_clock::now();
Player Engine::player = Player();

void Engine::init() {
	Graphics::init();
	PlayerBindingEvent::player = &player;

	EventController::level = std::vector<LevelEvent*>();
	EventController::currentTime = &currentTime;
	uint vertexCount = 4;
	float* vertexCoords = new float[] {0.f, 0.f, 0.f, 1.f, 1.f, 0.f, 1.f, 1.f};
	float* vertexColors = new float[] {0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 1.f};
	uint* vertexIDs = new uint[]{ 0, 1, 2, 1, 2, 3 };
	uint EBOsize = 6;

	Shape* shape = new Shape(vertexCount, vertexCoords, vertexColors, EBOsize, vertexIDs);

	ShapeSpawnEvent* ev = new ShapeSpawnEvent(shape, 0, 0);

	PlayerBindingEvent* a = new PlayerBindingEvent(0, 0);

	EventController::level.push_back(ev);
	EventController::level.push_back(a);
	

//	EventController::saveLevel("a", EventController::level);
//	EventController::loadLevel("a");
}

void Engine::pollEvents() {
	glfwPollEvents();
}

void Engine::update() {
	pollEvents();
	auto end = std::chrono::system_clock::now();
	currentTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	EventController::updateActiveEventList();
}

void Engine::render() {
	Graphics::draw();
}

bool Engine::running() {
	return Graphics::running();
}