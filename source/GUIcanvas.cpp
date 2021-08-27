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

bool GUIcanvas::isButtonActive = false;
bool GUIcanvas::mouseButtonStates[] = {false, false, false};

double GUIcanvas::mousePositionX = 0;
double GUIcanvas::mousePositionY = 0;

int GUIcanvas::windowWidth = 0;
int GUIcanvas::windowHeight = 0;

GLFWwindow* GUIcanvas::window = nullptr;
ShapeController* GUIcanvas::shapeController = nullptr;

std::list<GUIobject*> GUIcanvas::GUIobjects;
std::list<GUIinteractiveObject*> GUIcanvas::GUIinteractiveObjects;

std::list<GUIinteractiveObject*>::iterator GUIcanvas::currentInteractiveObject;

std::vector<int> GUIcanvas::activatedButtonIndexes(0);


void GUIcanvas::update() {
	activatedButtonIndexes.clear();
	glfwGetCursorPos(window, &mousePositionX,  &mousePositionY);
	for (int i = 0; i < sizeof(mouseButtonStates); i++) {
		mouseButtonStates[i] = glfwGetMouseButton(window, i);
	}
	GUIcanvas::interact();
}

void GUIcanvas::interact() {
	if (isButtonActive) {
		if (!(*currentInteractiveObject)->interact(mouseButtonStates, (float)mousePositionX, (float)mousePositionY)) {
			GUIinteractiveObject::resetInterationData();
			isButtonActive = false;
		}
	}
	else for (auto it = GUIinteractiveObjects.begin(); it != GUIinteractiveObjects.end(); it++) {
		(*it)->interact(mouseButtonStates, (float)mousePositionX, (float)mousePositionY);
		if ((*it)->interact(mouseButtonStates, (float)mousePositionX, (float)mousePositionY)) {
			isButtonActive = true;
			currentInteractiveObject = it;
		}
	}
}

const std::vector<int>& GUIcanvas::getActivatedButtonIndexes() {
	return activatedButtonIndexes;
}

void GUIcanvas::draw() {
	shapeController->draw();
}

std::list<GUIinteractiveObject*>::iterator GUIcanvas::addSex(
	Vector2f position,
	Vector2f size
) {
	GUIinteractiveObjects.push_back(new ButtonSex(position, size, shapeController));
	return --GUIinteractiveObjects.end();
}

std::list<GUIinteractiveObject*>::iterator GUIcanvas::addSlider(
	Vector2f position,
	Vector2f size,
	float* x,
	float* y,
	Vector2f min,
	Vector2f max
) {
	GUIinteractiveObjects.push_back(new Slider(position, size, x, y, min, max, shapeController));
	return --GUIinteractiveObjects.end();
}

std::list<GUIinteractiveObject*>::iterator GUIcanvas::addCheckBox(Vector2f position, Vector2f size, bool* value) {
	GUIinteractiveObjects.push_back(new CheckBox(position, size, shapeController, value));
	return --GUIinteractiveObjects.end();
}

std::list<GUIinteractiveObject*>::iterator GUIcanvas::addActionButton(
	Vector2f position,
	Vector2f size, 
	int buttonIndex,
	Color activeColor,
	Color passiveColor 
) {
	GUIinteractiveObjects.push_back(new ActionButton(position, size, shapeController, buttonIndex, &activatedButtonIndexes, activeColor, passiveColor));
	return --GUIinteractiveObjects.end();
}

std::list<GUIobject*>::iterator GUIcanvas::addGUIobject(ShapeGroup shapeGroup) {
	GUIobjects.push_back(new GUIobject(shapeGroup, shapeController));
	return --GUIobjects.end();
}

void GUIcanvas::removeObject(std::list<GUIinteractiveObject*>::iterator objectID) {
	bool isIteratorValid = false;
	for (auto it = GUIinteractiveObjects.begin(); it != GUIinteractiveObjects.end(); it++) {
		if (it == objectID) {
			isIteratorValid = true;
			break;
		}
	}
	if (isIteratorValid) {
		if (objectID == currentInteractiveObject) {
			isButtonActive = false;
		}
		shapeController->removeShapeGroup((*objectID)->getShapeGroup());
		GUIinteractiveObjects.erase(objectID);
	} else {
		throw std::logic_error("ti soisvolil udolit udalennuiu knopku, ZHIVOTNOE");
	}
}

void GUIcanvas::removeObject(std::list<GUIobject*>::iterator objectID) {
	bool isIteratorValid = false;
	for (auto it = GUIobjects.begin(); it != GUIobjects.end(); it++) {
		if (it == objectID) {
			isIteratorValid = true;
			break;
		}
	}
	if (isIteratorValid) {
		shapeController->removeShapeGroup((*objectID)->getShapeGroup());
		GUIobjects.erase(objectID);
	}
	else {
		throw std::logic_error("ti soisvolil udolit udalenniy object, ZVERINKA");
	}
}

void GUIcanvas::clear() {
	isButtonActive = false;
	shapeController->reset();

	GUIobjects.clear();
	GUIinteractiveObjects.clear();
}

void GUIcanvas::reset() {
	GUIcanvas::clear();
	delete shapeController;
	shapeController = nullptr;
}

void GUIcanvas::setWindow() {
	GUIcanvas::window = Window::getWindow();
	GUIcanvas::windowWidth = Window::getWidth();
	GUIcanvas::windowHeight = Window::getHeight();
}

void GUIcanvas::init(ShapeController* shapeController) {
	GUIcanvas::shapeController = shapeController;
	GUIinteractiveObject::resetInterationData();
}
