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
	float positionX, 
	float positionY,
	float sizeX, 
	float sizeY
) {
	float vertexCoords[] = {0.f, 0.f, 0.f, sizeY, sizeX, 0.f, sizeX, sizeY};
	float vertexColors[] = {1.f, 0.f, 0.f, 1.f, 1.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 1.f};
	uint vertexIDs[] = {0, 1, 2, 1, 2, 3};
	
	Shape shape[] = {Shape (4, vertexCoords, vertexColors, 6, vertexIDs, 1.f, 0.f, 0.f, 0)};
	ButtonSex* buttonSex = new ButtonSex(ShapeGroup(1, shape, 1.f, positionX, positionY, 0), shapeController);
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
