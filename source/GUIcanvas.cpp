#include "GUIcanvas.h"
#include <iostream>
#include "crtdbg.h"
#include "..\include\CRTDBG\mydbgnew.h"
#ifdef _DEBUG
#define new MYDEBUG_NEW
#endif

bool GUIcanvas::mouseButtonStates[] = {false, false, false};
double GUIcanvas::mousePositionX = 0;
double GUIcanvas::mousePositionY = 0;
GLFWwindow* GUIcanvas::window = nullptr;
ShapeController* GUIcanvas::shapeController = nullptr;

std::vector<GUIinteractiveObject*> GUIcanvas::objects(0);

int GUIcanvas::currentButtonID = -1;

void GUIcanvas::update() {

	glfwGetCursorPos(window, &mousePositionX,  &mousePositionY);
	for (int i = 0; i < sizeof(mouseButtonStates); i++) {
		mouseButtonStates[i] = glfwGetMouseButton(window, i);
	}
	GUIcanvas::interact();
}

void GUIcanvas::interact() {
	if (currentButtonID >= 0) {
		if (!objects[currentButtonID]->interact(mouseButtonStates, (float)mousePositionX, (float)mousePositionY)) {
			currentButtonID = -1;
			
		}
	}
	else
	for (int i = 0; i < objects.size(); i++) {
		if (objects[i]->interact(mouseButtonStates, (float)mousePositionX, (float)mousePositionY)) {
			currentButtonID = i;
		}
	}
}

void GUIcanvas::draw() {
	shapeController->draw();
}

void GUIcanvas::addGUIobject(GUIinteractiveObject* object) {
	objects.push_back(object);
	shapeController->addShapeGroup(object->getShapeGroup());
}

void GUIcanvas::setWindow(GLFWwindow* window) {
	GUIcanvas::window = window;
}

void GUIcanvas::init() {
	GUIcanvas::shapeController = new ShapeController();
}
