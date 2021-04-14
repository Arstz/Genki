#pragma once
#include "Player.h"
#include "ShapeController.h"
#include <chrono>
#include <iostream>
#include "..\include\GLFW\glfw3.h"

class Engine {

private:
	static void pollEvents();

	static float currentTime;
	static float frameTime;
	static std::chrono::system_clock::time_point start;
	static GLFWwindow* window;
	static ShapeController levelShapeController;
	static Player player;


public:
	static void init();
	static void update();
	static void render();
	static void destroy();
	static void terminate();
	static bool running();
	static void pollKeyEvents();
};

