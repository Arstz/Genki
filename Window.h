#pragma once
#define GLEW_STATIC

#include "GL\glew.h"
#include "GLFW\glfw3.h"

typedef unsigned int uint;

class Window {
public:
	
	static GLFWwindow* window;
	static float backgroundColor[4];
	static GLuint currentBufferID;

	static GLuint generateBufferID();
	static void init();
	static GLFWwindow* getWindow();
	static float* getBackgroundColorValuePointer(uint valueNum);
	static bool running();
	static void clear();
};

