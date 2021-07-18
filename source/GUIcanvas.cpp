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
ButtonType GUIcanvas::ButtonState::type = ButtonType::EMPTY;
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
		switch (ButtonState::type) {
		case ButtonType::BUTTON_SEX:
			if (!CURRENT_BUTTON_SEX->state && mouseButtonStates[0]) {
				std::cout << "sex\n";
				CURRENT_BUTTON_SEX->state = true;
			}
			if (!mouseButtonStates[0]) {
				CURRENT_BUTTON_SEX->state = false;
				currentButtonID = -1;
				ButtonState::type = ButtonType::EMPTY;
			}
			break;
		case ButtonType::BUTTON:
			if (!CURRENT_BUTTON->state && mouseButtonStates[0]) {
				std::cout << "button\n";
				CURRENT_BUTTON->state = true;
			}
			if (!mouseButtonStates[0]) {
				CURRENT_BUTTON->state = false;
				currentButtonID = -1;
				ButtonState::type = ButtonType::EMPTY;
			}
			break;
		case ButtonType::SLIDER:
			if (!CURRENT_SLIDER->state && mouseButtonStates[0]) {
				CURRENT_SLIDER->state = true;
				std::cout << CURRENT_SLIDER->cursorPointerX << '\n';
				*(CURRENT_SLIDER->cursorPointerX) += 1;
			}
			if (!mouseButtonStates[0]) {
				CURRENT_SLIDER->state = false;
				currentButtonID = -1;
				ButtonState::type = ButtonType::EMPTY;				
			}
		}
	}
	else
	for (int i = 0; i < objects.size(); i++) {
		if (objects[i]->checkCollision((float)mousePositionX, (float)mousePositionY)) {
			currentButtonID = i;
			ButtonState::type = objects[i]->getType();
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

void GUIcanvas::setWindow() {
	GUIcanvas::window = Window::getWindow();
	GUIcanvas::windowWidth = Window::getWidth();
	GUIcanvas::windowHeight = Window::getHeight();
}

void GUIcanvas::init() {
	GUIcanvas::shapeController = new ShapeController();
}
