#include "crtdbg.h"
#include "..\include\CRTDBG\mydbgnew.h"

#include <iostream>
#include "GUI.h"
#include "Window.h"
#include <initializer_list>
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

	Vector2f bordersX(shapeController->valueToPx(Vector2f(positionX + minX, positionY + maxY)));
	Vector2f bordersY(shapeController->valueToPx(Vector2f(positionX + maxX, positionY + minY)));

	this->LeftBorderX = bordersX.x;
	this->RightBorderX = bordersY.x;
	this->UpBorderY = bordersX.y;
	this->BottomBorderY = bordersY.y;
}

GUIinteractiveObject::GUIinteractiveObject(ShapeGroup&& shapeGroup, ShapeController* shapeController) : GUIobject(shapeGroup, shapeController) {
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

	Vector2f bordersX(shapeController->valueToPx(Vector2f(positionX + minX, positionY + maxY)));
	Vector2f bordersY(shapeController->valueToPx(Vector2f(positionX + maxX, positionY + minY)));

	this->LeftBorderX = bordersX.x;
	this->RightBorderX = bordersY.x;
	this->UpBorderY = bordersX.y;
	this->BottomBorderY = bordersY.y;
}

bool GUIinteractiveObject::checkCollision(float x, float y) {
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

ButtonSex::ButtonSex(Vector2f position,	Vector2f size, ShapeController* shapeController) : GUIinteractiveObject(
	ShapeGroup(1, (Shape*)std::begin(std::initializer_list<Shape> {Shape(4,
		(float*)std::begin(std::initializer_list<float> { 0.f, 0.f, 0.f, size.y, size.x, 0.f, size.x, size.y }),
		(float*)std::begin(std::initializer_list<float> { 1.f, 0.f, 0.f, 1.f, 1.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 1.f}),
		6,
		(uint*)std::begin(std::initializer_list<uint> { 0, 1, 2, 1, 2, 3 })
		,1.f,
		0.f,
		0.f, 
		0.f )}),
		1.f, position.x, position.y, 0),
	shapeController
) {
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
