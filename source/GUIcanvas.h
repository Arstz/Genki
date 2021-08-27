#pragma once
#define GLEW_STATIC

#include "..\include\GL\glew.h"
#include "..\include\GLFW\glfw3.h"

#include "Window.h"
#include <vector>
#include "GUI/GUI.h"
#include "Vector2f.h"
#include "ShapeController.h"
#include "AnimationController.h"

class GUIcanvas {
private:
	static bool isButtonActive;
	static bool mouseButtonStates[3];

	static double mousePositionX;
	static double mousePositionY;

	static int windowWidth;
	static int windowHeight;

	static GLFWwindow* window;
	static ShapeController* shapeController;

	static std::list<GUIobject*> GUIobjects;
	static std::list<GUIinteractiveObject*> GUIinteractiveObjects;
	static std::list<GUIinteractiveObject*>::iterator currentInteractiveObject;		

	static std::vector<int> activatedButtonIndexes;

	static void interact();	
public:	
	static void draw();
	static void clear();
	static void reset();
	static void update();
	static void setWindow();
	static void init(ShapeController* shapeController);
	static void removeObject(std::list<GUIobject*>::iterator objectID);
	static void removeObject(std::list<GUIinteractiveObject*>::iterator objectID);	

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
	static std::list<GUIobject*>::iterator addGUIobject(ShapeGroup shapeGroup);	
};
