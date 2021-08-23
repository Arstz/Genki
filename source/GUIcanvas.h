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
	static std::list<GUIinteractiveObject*>::iterator currentInteractiveObject;
	static bool isButtonActive;

	static int windowWidth;
	static int windowHeight;

	static GLFWwindow* window;
	static std::list<GUIinteractiveObject*> objects;
	
	static void interact();
	static std::vector<int> activatedButtonIndexes;
	

public:
	static ShapeController* shapeController;
	static void setWindow();
	static void init(ShapeController* shapeController);
	static void update();
	static void draw();
	static const std::vector<int>& getActivatedButtonIndexes();
	static std::list<GUIinteractiveObject*>::iterator addSex(
		Vector2f position,
		Vector2f size
	);
	static std::list<GUIinteractiveObject*>::iterator addSlider(
		Vector2f position,
		Vector2f size,
		float* x,
		float* y,
		Vector2f min,
		Vector2f max
	);
	static std::list<GUIinteractiveObject*>::iterator addCheckBox(
		Vector2f position,
		Vector2f size,
		bool* value
	);
	static std::list<GUIinteractiveObject*>::iterator addActionButton(
		Vector2f position,
		Vector2f size,
		int buttonIndex,
		Color activeColor = Color(0.f, 0.f, 0.f, 1.f),
		Color passiveColor = Color(0.f, 0.f, 0.f, 1.f)
	);
	static void removeObject(std::list<GUIinteractiveObject*>::iterator objectID);
	static void clear();
};
