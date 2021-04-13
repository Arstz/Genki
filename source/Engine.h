#pragma once
#include "Player.h"
#include "ShapeController.h"
#include <chrono>
#include <iostream>
#include "..\include\GLFW\glfw3.h"

class Engine {

private:
	void pollEvents();

	float currentTime;
	float frameTime;
	std::chrono::system_clock::time_point start;
	GLFWwindow* window;
	ShapeController levelShapeController;
	Player player;

public:
	void init();
	
	void update();
	void render();

	void destroy();
	void terminate();
	bool running();
	void pollKeyEvents();

	Engine();
};

