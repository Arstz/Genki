#pragma once
#define GLEW_STATIC

#include "..\include\GL\glew.h"
#include "..\include\GLFW\glfw3.h"

#include "Window.h"
#include <vector>
#include "GUI.h"
#include "ShapeController.h"
#include "AnimationController.h"

class GUIcanvas {
private:
	class ButtonState {
	public:
		static ButtonType type;

	};

	static double mousePositionX;
	static double mousePositionY;
	static bool mouseButtonStates[3];
	static int currentButtonID;

	static int windowWidth;
	static int windowHeight;

	static GLFWwindow* window;
	static std::vector<GUIinteractiveObject*> objects;
	static ShapeController* shapeController;
	static void interact();

public:
	static void setWindow();
	static void init();
	static void update();
	static void draw();
	static void addGUIobject(GUIinteractiveObject* object);
};
