#pragma once
#define GLEW_STATIC

#include "..\include\GL\glew.h"
#include "..\include\GLFW\glfw3.h"

typedef unsigned int uint;

class Window {
	static GLFWwindow* window;
	static float backgroundColor[4];
	static int width;
	static int height;
public:
	static void init(int width, int height);
	static GLFWwindow* getWindow();
	static float* getBackgroundColorValuePointer(uint valueNum);
	static bool running();
	static void clear();
	static int getWidth();
	static int getHeight();
};

