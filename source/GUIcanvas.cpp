#include "GUIcanvas.h"
#include <iostream>
#include "crtdbg.h"
#include "..\include\CRTDBG\mydbgnew.h"
#define CURRENT_BUTTON_SEX ((ButtonSex*)&objects[currentButtonID])
#define CURRENT_BUTTON ((Button*)&objects[currentButtonID])
#define CURRENT_SLIDER ((Slider*)&objects[currentButtonID])
#ifdef _DEBUG
#define new MYDEBUG_NEW
#endif

bool GUIcanvas::mouseButtonStates[] = {false, false, false};
double GUIcanvas::mousePositionX = 0;
double GUIcanvas::mousePositionY = 0;
GLFWwindow* GUIcanvas::window = nullptr;
ShapeController* GUIcanvas::shapeController = nullptr;
std::vector<GUIinteractiveObject*> GUIcanvas::objects(0);
int GUIcanvas::windowWidth = 0;
int GUIcanvas::windowHeight = 0;
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
	} else for (int i = 0; i < objects.size(); i++) {
		objects[i]->interact(mouseButtonStates, (float)mousePositionX, (float)mousePositionY);
		if (objects[i]->interact(mouseButtonStates, (float)mousePositionX, (float)mousePositionY)) {
			currentButtonID = i;
		}
	}
}

void GUIcanvas::draw() {
	shapeController->draw();
}

void GUIcanvas::addSex(
	Vector2f position,
	Vector2f size
) {
	ButtonSex* buttonSex = new ButtonSex(position, size, shapeController);
	objects.push_back(buttonSex);
}

void GUIcanvas::setWindow() {
	GUIcanvas::window = Window::getWindow();
	GUIcanvas::windowWidth = Window::getWidth();
	GUIcanvas::windowHeight = Window::getHeight();
}

void GUIcanvas::init() {
	GUIcanvas::shapeController = new ShapeController();
}
