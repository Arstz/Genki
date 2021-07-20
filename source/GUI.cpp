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

	Vector2f bordersX(shapeController->engineCoordsToScreenCoords(Vector2f(positionX + minX, positionY + maxY)));
	Vector2f bordersY(shapeController->engineCoordsToScreenCoords(Vector2f(positionX + maxX, positionY + minY)));

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
	
	setBorders(0);

}

GUIinteractiveObject::GUIinteractiveObject(ShapeGroup&& shapeGroup, ShapeController* shapeController, int shapeID) : GUIobject(shapeGroup, shapeController) {
	Shape* shapes = shapeGroup.getShapesPointer();
	if (shapes == nullptr) {
		throw std::exception("Failed to find shape inside shapegroup");
	}
	setBorders(shapeID);
}

GUIinteractiveObject::GUIinteractiveObject(std::list<ShapeGroup>::iterator shapeGroup, ShapeController* shapeController, int shapeID) : GUIobject(shapeGroup, shapeController){
	Shape* shapes = shapeGroup->getShapesPointer();
	if (shapes == nullptr) {
		throw std::exception("Failed to find shape inside shapegroup");
	}
	setBorders(shapeID);
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
	shapeController,
	0
) {
	this->state = false;
}

Button::Button(ShapeGroup& shapeGroup, ShapeController* shapeController) : GUIinteractiveObject(shapeGroup, shapeController) {
	this->state = false;
}

Slider::Slider(
	Vector2f position,
	Vector2f size,
	float* valueX,
	float* valueY,
	Vector2f min,
	Vector2f max,
	ShapeController* shapeController,
	float cursorSize
) : GUIinteractiveObject(	
	std::move(ShapeGroup(
		2,
		(Shape*)std::begin(std::initializer_list<Shape> {
			std::move(Shape::makeRectangle(Vector2f(0, 0), Vector2f(std::max(size.x, cursorSize), std::max(size.y, cursorSize)), Vector2f(0, 0), Color(0.5, 0.5, 0.5, 1.f), 0)),
			std::move(Shape::makeRectangle(Vector2f(-cursorSize /2, -cursorSize / 2), Vector2f(cursorSize / 2, cursorSize / 2), Vector2f(cursorSize / 2, cursorSize / 2), Color(0, 0, 0, 1), 1))
		}),
		1.f,
		position.x,
		position.y,
		0
	)),
	shapeController, 
	0
	) {
	cursor = GUIinteractiveObject(shapeGroup, shapeController, 1);
	this->size = Vector2f(std::max(size.x, cursorSize), std::max(size.y, cursorSize));
	this->valueX = valueX;
	this->valueY = valueY;
	this->min = min;
	this->max = max;
	this->cursorSize = cursorSize;
	this->position = position;
}

bool Slider::interact(bool mouseButtonStates[3], float x, float y) {
	if (interactionData.isActive) { //If in last frame cursor was active
		if (mouseButtonStates[0]) {
			update:
			Vector2f pos(x, y);
			Vector2f cursorSizePx(shapeController->valueToPx(Vector2f(cursorSize / 2, cursorSize / 2)));
			pos.x = std::max(pos.x, LeftBorderX + cursorSizePx.x); //aaaa
			pos.x = std::min(pos.x, RightBorderX - cursorSizePx.x);
			pos.y = std::min(pos.y, BottomBorderY - cursorSizePx.y);
			pos.y = std::max(pos.y, UpBorderY + cursorSizePx.y);

			pos = shapeController->screenCoordsToEngineCoords(pos);

			*shapeGroup->getShapesPointer()[1].getPositionXpointer() = pos.x - *shapeGroup->getPositionXpointer();
			*shapeGroup->getShapesPointer()[1].getPositionYpointer() = pos.y - *shapeGroup->getPositionYpointer();

			*valueX = (pos.x - position.x - cursorSize) / (size.x - cursorSize) * (max.x - min.x) + min.x;
			*valueY = (pos.y - position.y - cursorSize) / (size.y - cursorSize) * (max.y - min.y) + min.y;
		} else {			
			if (checkCollision(x, y)) {
				interactionData.isActive = false;	
				shapeGroup->getShapesPointer()[1].setColor(Color(0, 0, 0, 1));
				cursor.setBorders(1);
				if (cursor.checkCollision(x, y)) {
					shapeGroup->getShapesPointer()[1].setColor(Color(1, 1, 1, 1));
					interactionData.lastCollisionCheckResult = true;
				}
				else {
					interactionData.lastCollisionCheckResult = false;
				}
			}
			else {
				cursor.setBorders(1);
				return false; 
			}
		}
	}
	else {
		if (checkCollision(x, y)) {
			if (mouseButtonStates[0]) {
				interactionData.isActive = true;
				shapeGroup->getShapesPointer()[1].setColor(Color(0, 0.5, 1, 1));
				goto update;
			}
			else {
				if (cursor.checkCollision(x, y)) {
					if (!interactionData.lastCollisionCheckResult) {
						shapeGroup->getShapesPointer()[1].setColor(Color(1, 1, 1, 1));
					}
					interactionData.lastCollisionCheckResult = true;
				}
				else if (interactionData.lastCollisionCheckResult == true) {
					interactionData.lastCollisionCheckResult = false;
					shapeGroup->getShapesPointer()[1].setColor(Color(0, 0, 0, 1));
				}
			}
		}
		else {
			shapeGroup->getShapesPointer()[1].setColor(Color(0, 0, 0, 1));
			return false; //If mouse cursor leaves padding area
		}
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
