#include "Engine.h"
#include "EventController.h"
#include "Shape.h"
#include "LevelEvent.h"
#include "Graphics.h"
#define AAAA (static_cast <float> (rand()) / static_cast <float> (RAND_MAX))

float Engine::currentTime = 0;
std::chrono::system_clock::time_point Engine::start = std::chrono::system_clock::now();
Player Engine::player = Player();

void Engine::init() {
	Graphics::init();
	PlayerBindingEvent::player = &player;

	EventController::level = std::vector<LevelEvent*>();
	EventController::currentTime = &currentTime;
	for (int i = 0; i < 3000; i++){
		uint vertexCount = 3;
	float* vertexCoords = new float[] {AAAA, AAAA, AAAA, AAAA, AAAA, AAAA};
	float* vertexColors = new float[] {AAAA, AAAA, AAAA, AAAA, AAAA, AAAA, AAAA, AAAA, AAAA, AAAA, AAAA, AAAA};
	uint* vertexIDs = new uint[]{ 0, 1, 2 };
	uint EBOsize = 3;

	Shape shape(vertexCount, vertexCoords, vertexColors, EBOsize, vertexIDs);

	ShapeSpawnEvent* ev = new ShapeSpawnEvent(shape, 0, 0);

	EventController::level.push_back(ev);
}
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