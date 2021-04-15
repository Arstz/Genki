#include "GUIcanvas.h"

bool GUIcanvas::mouseButtonStates[] = {false, false, false};
double GUIcanvas::mousePositionX = 0;
double GUIcanvas::mousePositionY = 0;
ShapeController GUIcanvas::shapeController = ShapeController();
GLFWwindow* GUIcanvas::window = nullptr;
std::vector<GUIinteractiveObject*> GUIcanvas::objects(0);

void GUIcanvas::update() {
	glfwGetCursorPos(window, &mousePositionX,  &mousePositionY);
	for (int i = 0; i < sizeof(mouseButtonStates); i++) {
		mouseButtonStates[i] = glfwGetMouseButton(window, i);
	}
	GUIcanvas::interact();
}

void GUIcanvas::interact() {
	for (int i = 0; i < objects.size(); i++) {
		objects[i]->interact(mouseButtonStates, (float)mousePositionX, (float)mousePositionY);
	}
}

void GUIcanvas::draw() {
	shapeController.draw();
}

void GUIcanvas::setWindow(GLFWwindow* window) {
	GUIcanvas::window = window;
}

void GUIcanvas::init() {
	GUIcanvas::shapeController = ShapeController();
}
