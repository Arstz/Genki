#pragma once
#define GLEW_STATIC

#include "..\include\GL\glew.h"
#include "..\include\GLFW\glfw3.h"

#include <vector>
#include "GUI.h"
#include "ShapeController.h"

class GUIcanvas
{
private:
	static double mousePositionX;
	static double mousePositionY;
	static bool mouseButtonStates[3];
	
	static GLFWwindow* window;
	static std::vector<GUIinteractiveObject*> objects;
	static ShapeController shapeController;
	static void interact();
public:
	static void setWindow(GLFWwindow* window);
	static void init();
	static void update();
	static void draw();
};
