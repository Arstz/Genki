#pragma once
#include "Player.h"
#include "ShapeController.h"
#include <chrono>
#include <iostream>
#include "GUIcanvas.h"
#include "..\include\GLFW\glfw3.h"

typedef void (*EngineFunction)();

class Engine {
private:

	//engine data

	static GLFWwindow* window;
	static int width;
	static int height;

	static EngineFunction currentFunction;

	static std::vector<ShapeController*> shapeControllers;
	static std::vector<Shader*> shaders;

	static void init();
	static void initShaders();
	static void pollEvents();

	static void sex();

	//main menu data

	static void initMainMenu();
	static void updateMainMenu();

	//game data

	static void initGame();
	static void updateGame();

	//editor data

	static void initEditor();
	static void updateEditor();

	//test data

	static float currentTime;
	static float frameTime;
	static std::chrono::system_clock::time_point start;

	static Player player;

	static std::list<GUIinteractiveObject*>::iterator zhertva;

	static void initTest();
	static void updateTest();
	static void initGUI();
	static void pollKeyEvents();

public:

	//engine data

	static void callUpdate();
	static bool running();
	static void destroy();
	static void terminate();

};

