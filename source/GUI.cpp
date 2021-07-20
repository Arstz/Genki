#include "crtdbg.h"
#include "..\include\CRTDBG\mydbgnew.h"

#include <iostream>
#include "GUI.h"
#include "Window.h"
#include <initializer_list>
#ifdef _DEBUG
#define new MYDEBUG_NEW
#endif

GUIinteractiveObject::InteractionData GUIinteractiveObject::interactionData = GUIinteractiveObject::InteractionData();

GUIobject::~GUIobject() {}
GUIobject::GUIobject() {}

GUIobject::GUIobject(const ShapeGroup& shapeGroup, ShapeController* shapeController) {
	this->shapeGroup = shapeController->addShapeGroup(shapeGroup);
	this->shapeController = shapeController;
}

GUIobject::GUIobject(std::list<ShapeGroup>::iterator shapeGroup, ShapeController* shapeController) {
	this->shapeGroup = shapeGroup;
	this->shapeController = shapeController;
}

void GUIinteractiveObject::setBorders(int shapeID) {
	Shape* shape = &shapeGroup->getShapesPointer()[shapeID];
	float minX, minY, maxX, maxY;
	std::tie(minX, minY, maxX, maxY) = shape->getBounds();

//	float* coords = shape->getVertexCoordsPointer();
	float positionX = *shape->getPositionXpointer() + *shapeGroup->getPositionXpointer();
	float positionY = *shape->getPositionYpointer() + *shapeGroup->getPositionYpointer();

	Vector2f bordersX(shapeController->valueToPx(Vector2f(positionX + minX, positionY + maxY)));
	Vector2f bordersY(shapeController->valueToPx(Vector2f(positionX + maxX, positionY + minY)));

	this->LeftBorderX = bordersX.x;
	this->RightBorderX = bordersY.x;
	this->UpBorderY = bordersX.y;
	this->BottomBorderY = bordersY.y;
}

void GUIinteractiveObject::resetInteratiocData() {
	interactionData.reset();
}

GUIinteractiveObject::GUIinteractiveObject() {

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

	setBorders(0);
}

GUIinteractiveObject::GUIinteractiveObject(std::list<ShapeGroup>::iterator shapeGroup, ShapeController* shapeController) : GUIobject(shapeGroup, shapeController){
	Shape* shapes = shapeGroup->getShapesPointer();
	if (shapes == nullptr) {
		throw std::exception("Failed to find shape inside shapegroup");
	}
	if (shapes[0].getVertexCount() != 4) {
		throw std::exception("Shape is not a tetragon");
	}
	setBorders(0);
}

bool GUIinteractiveObject::checkCollision(float x, float y) {
	return x < RightBorderX && x > LeftBorderX && y > UpBorderY && y < BottomBorderY;
}

bool GUIinteractiveObject::interact(bool mouseButtonStates[3], float x, float y) {
	return false;
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

ButtonSex::ButtonSex(Vector2f position, 
	Vector2f size, 
	ShapeController* shapeController
) : GUIinteractiveObject(
	ShapeGroup(1, (Shape*)std::begin(std::initializer_list<Shape> {
			std::move(Shape::makeRectangle(
				Vector2f(0, 0),
				size,
				Vector2f(0, 0),
				Color(1.f, 1.f, 0.f, 1.f)
			))
		}),
		1.f, 
		position.x, 
		position.y,
		0
	),
	shapeController
) {
	this->state = false;
}

Button::Button(ShapeGroup& shapeGroup, ShapeController* shapeController) : GUIinteractiveObject(shapeGroup, shapeController) {
	this->state = false;
}

Slider::Slider(
	Vector2f position,
	Vector2f size,
	float* x,
	float* y,
	Vector2f min,
	Vector2f max,
	ShapeController* shapeController
) : GUIinteractiveObject(
	ShapeGroup(
		2,
		(Shape*)std::begin(std::initializer_list<Shape> {
			Shape::makeRectangle(Vector2f(0, 0), size, Vector2f(0, 0), Color(0.5, 0.5, 0.5, 1.f), 0),
			Shape::makeRectangle(Vector2f(-1, -1), Vector2f(1, 1), Vector2f(1, 1), Color(0, 0, 0, 1), 1)
		}),
		1.f,
		position.x,
		position.y,
		0
	),
	shapeController) {
	cursor = GUIinteractiveObject(shapeGroup, shapeController);
	this->x = x;
	this->y = y;
	this->min = min;
	this->max = max;
}

bool Slider::interact(bool mouseButtonStates[3], float x, float y) {
	if (interactionData.isActive) {
		if (mouseButtonStates[0]) {
			Vector2f pos(shapeController->pxToValue(Vector2f(x, y)));
			*shapeGroup->getShapesPointer()[1].getPositionXpointer() = pos.x - *shapeGroup->getPositionXpointer();
			*shapeGroup->getShapesPointer()[1].getPositionYpointer() = pos.y - *shapeGroup->getPositionYpointer();
			
		} else {
			cursor.setBorders(1);
			if (checkCollision(x, y))
				interactionData.isActive = false;
			else return false;
		}
	}
	else {
		if (checkCollision(x, y)) {
			if (mouseButtonStates[0])
			interactionData.isActive = true;
		}
		else return false;
	}
	return true;
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
