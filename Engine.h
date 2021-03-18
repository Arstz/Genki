#pragma once
#include "Player.h"
#include <chrono>
#include <iostream>
#include "GLFW/glfw3.h"

class Engine
{

private:
	static void pollEvents();

	static float currentTime;
	static std::chrono::system_clock::time_point start;
	static GLFWwindow* window;

	static Player player;

public:
	static void init();
	
	static void update();
	static void render();

	static bool running();
	static void pollKeyEvents();
};

