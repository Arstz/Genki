#pragma once
#define GLEW_STATIC

#include "..\include\GL\glew.h"
#include "..\include\GLFW\glfw3.h"

#include "Window.h"
#include <vector>
#include "GUI.h"
#include "Vector2f.h"
#include "ShapeController.h"
#include "AnimationController.h"

class GUIcanvas {
private:
	static double mousePositionX;
	static double mousePositionY;
	static bool mouseButtonStates[3];
	static int currentButtonID;

	static int windowWidth;
	static int windowHeight;

	static GLFWwindow* window;
	static std::vector<GUIinteractiveObject*> objects;
	
	static void interact();

public:
	static ShapeController* shapeController;
	static void setWindow();
	static void init();
	static void update();
	static void draw();
	static void addSex(
		Vector2f position,
		Vector2f size
	);
	static void addSlider(
		Vector2f position,
		Vector2f size,
		float* x,
		float* y,
		Vector2f min,
		Vector2f max
	);
};
