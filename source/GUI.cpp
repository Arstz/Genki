#include "crtdbg.h"
#include "..\include\CRTDBG\mydbgnew.h"

#include <iostream>
#include "GUI.h"
#include "Window.h"
#ifdef _DEBUG
#define new MYDEBUG_NEW
#endif

GUIobject::~GUIobject() {}

GUIobject::GUIobject(const ShapeGroup& shapeGroup, ShapeController* shapeController) {
	this->shapeGroup = shapeController->addShapeGroup(shapeGroup);
}

GUIinteractiveObject::GUIinteractiveObject(
	ShapeGroup& shapeGroup,
	ShapeController* shapeController

) : GUIobject(shapeGroup, shapeController) {
	Shape* shapes = shapeGroup.getShapesPointer();
	if (shapes == nullptr) {
		throw std::exception("Failed to find shape inside shapegroup");
	}
	if (shapes[0].getVertexCount() != 4) {
		throw std::exception("Shape is not a tetragon");
	}

	float minX, minY, maxX, maxY;
	std::tie(minX, minY, maxX, maxY) = shapes[0].getBounds();

	float* coords = shapes[0].getVertexCoordsPointer();
	float positionX = *shapes[0].getPositionXpointer() + *shapeGroup.getPositionXpointer();
	float positionY = *shapes[0].getPositionYpointer() + *shapeGroup.getPositionYpointer();

	this->LeftBorderX = Window::getWidth() / 2 + (positionX + minX) / 10 * Window::getHeight() / 2;
	this->RightBorderX = Window::getWidth() / 2 + (positionX + maxX) / 10 * Window::getHeight() / 2;
	this->UpBorderY = Window::getHeight() / 2 - (positionY + maxY) / 10 * Window::getHeight() / 2;
	this->BottomBorderY = Window::getHeight() / 2 - (positionY + minY) / 10 * Window::getHeight() / 2;
}

bool GUIinteractiveObject::checkCollision(float x, float y){
	//std::cout << x <<'\t' << y << std::endl;
	return x < RightBorderX && x > LeftBorderX && y > UpBorderY && y < BottomBorderY;
}


std::list<ShapeGroup>::iterator GUIobject::getShapeGroup() {
	return shapeGroup;
}

bool ButtonSex::interact(bool mouseButtonStates[3], float x, float y) {
	if (!state && checkCollision(x, y) && mouseButtonStates[0]) {
		std::cout << "sex\n";
		this->state = true;
	}
	if (!mouseButtonStates[0]) {
		this->state = false;
		return false;
	}

	return true;
}

ButtonSex::ButtonSex(ShapeGroup&& shapeGroup, ShapeController* shapeController) : GUIinteractiveObject(shapeGroup, shapeController) {
	this->state = false;
}


Button::Button(ShapeGroup& shapeGroup, ShapeController* shapeController) : GUIinteractiveObject(shapeGroup, shapeController) {
	this->state = false;
}

Slider::Slider(ShapeGroup&& shapeGroup, ShapeController* shapeController) : GUIinteractiveObject(shapeGroup, shapeController) {

}

bool Slider::interact(bool mouseButtonStates[3], float x, float y) {
	return false;
}

void GUIinteractiveObject::InteractionData::reset() {
	lastMouseButtonStates[0] = false;
	lastMouseButtonStates[1] = false;
	lastMouseButtonStates[2] = false;
	lastMousePositionX = 0;
	lastMousePositionY = 0;
	lastCollisionCheckResult = false;
	isActive = false;
}
