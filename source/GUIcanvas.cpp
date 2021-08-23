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
std::list<GUIinteractiveObject*> GUIcanvas::objects;
std::list<GUIinteractiveObject*>::iterator GUIcanvas::currentInteractiveObject;
int GUIcanvas::windowWidth = 0;
int GUIcanvas::windowHeight = 0;
bool GUIcanvas::isButtonActive = false;
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
			GUIinteractiveObject::resetInteratiocData();
			isButtonActive = false;
		}
	}
	else for (auto it = objects.begin(); it != objects.end(); it++) {
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
	objects.push_back(new ButtonSex(position, size, shapeController));
	return --objects.end();
}

std::list<GUIinteractiveObject*>::iterator GUIcanvas::addSlider(
	Vector2f position,
	Vector2f size,
	float* x,
	float* y,
	Vector2f min,
	Vector2f max
) {
	objects.push_back(new Slider(position, size, x, y, min, max, shapeController));
	return --objects.end();
}

std::list<GUIinteractiveObject*>::iterator GUIcanvas::addCheckBox(Vector2f position, Vector2f size, bool* value) {
	objects.push_back(new CheckBox(position, size, shapeController, value));
	return --objects.end();
}

std::list<GUIinteractiveObject*>::iterator GUIcanvas::addActionButton(
	Vector2f position,
	Vector2f size, 
	int buttonIndex
) {
	objects.push_back(new ActionButton(position, size, shapeController, buttonIndex, &activatedButtonIndexes, Color(1, 0, 0, 1), Color(0, 0, 0, 1)));
	return --objects.end();
}

void GUIcanvas::removeObject(std::list<GUIinteractiveObject*>::iterator objectID) {
	bool isIteratorValid = false;
	for (auto it = objects.begin(); it != objects.end(); it++) {
		if (it == objectID) {
			isIteratorValid = true;
			break;
		}
	}
	if (isIteratorValid) {
		shapeController->removeShapeGroup((*objectID)->getShapeGroup());
		objects.erase(objectID);
	} else {
		throw std::logic_error("ti soisvolil udolit udalennuiu knopku, ZHIVOTNOE");
	}
}

void GUIcanvas::clear() {
	for (auto& object : objects) {
		shapeController->removeShapeGroup(object->getShapeGroup());
	}
	objects.clear();
}

void GUIcanvas::setWindow() {
	GUIcanvas::window = Window::getWindow();
	GUIcanvas::windowWidth = Window::getWidth();
	GUIcanvas::windowHeight = Window::getHeight();
}

void GUIcanvas::init(ShapeController* shapeController) {
	GUIcanvas::shapeController = shapeController;
	GUIinteractiveObject::resetInteratiocData();
}
