#include "crtdbg.h"
#include "..\include\CRTDBG\mydbgnew.h"

#include <iostream>
#include <initializer_list>
#include <random>

#include "GUI.h"

#include "../Window.h"
#include "../Text.h"
#include "../GUIcanvas.h"


#ifdef _DEBUG
#define new MYDEBUG_NEW
#endif

GUIinteractiveObject::InteractionData GUIinteractiveObject::interactionData = GUIinteractiveObject::InteractionData();

GUIobject::GUIobject(
	const ShapeGroup& shapeGroup,
	ShapeController* shapeController
) :
	shapeGroup{shapeController->addShapeGroup(shapeGroup)},
	shapeController {shapeController}
{}

GUIobject::GUIobject(std::list<ShapeGroup>::iterator shapeGroup, ShapeController* shapeController) {
	this->shapeGroup = shapeGroup;
	this->shapeController = shapeController;
}

void GUIobject::processRequest(RequestType request, char data[REQUEST_DATA_SIZE]) {}


std::list<ShapeGroup>::iterator GUIobject::getShapeGroup() {
	return shapeGroup;
}

void GUIinteractiveObject::setBorders(int shapeID) {
	Shape* shape = &shapeGroup->getShapesPointer()[shapeID];
	float minX, minY, maxX, maxY;
	std::tie(minX, minY, maxX, maxY) = shape->getBounds();

	float positionX = *shape->getPositionXpointer() + *shapeGroup->getPositionXpointer();
	float positionY = *shape->getPositionYpointer() + *shapeGroup->getPositionYpointer();

	Vector2f bordersX(shapeController->engineCoordsToScreenCoords(Vector2f(positionX + minX, positionY + maxY)));
	Vector2f bordersY(shapeController->engineCoordsToScreenCoords(Vector2f(positionX + maxX, positionY + minY)));

	this->LeftBorderX = bordersX.x;
	this->RightBorderX = bordersY.x;
	this->UpBorderY = bordersX.y;
	this->BottomBorderY = bordersY.y;
}

void GUIinteractiveObject::resetInterationData() {
	interactionData.reset();
}

GUIinteractiveObject::GUIinteractiveObject(
	ShapeGroup& shapeGroup,
	ShapeController* shapeController

) : GUIobject(shapeGroup, shapeController) {
	if (shapeGroup.getShapesPointer() == nullptr) {
		throw std::exception("Failed to find shape inside shapegroup");
	}
	
	setBorders(0);

}

GUIinteractiveObject::GUIinteractiveObject(
	ShapeGroup&& shapeGroup, 
	ShapeController* shapeController, 
	int shapeID
) : GUIobject(shapeGroup, shapeController) {
	if (shapeGroup.getShapesPointer() == nullptr) {
		throw std::exception("Failed to find shape inside shapegroup");
	}
	setBorders(shapeID);
}

GUIinteractiveObject::GUIinteractiveObject(
	std::list<ShapeGroup>::iterator shapeGroup, 
	ShapeController* shapeController, 
	int shapeID
) : GUIobject(shapeGroup, shapeController){
	if (shapeGroup->getShapesPointer() == nullptr) {
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

void GUIinteractiveObject::InteractionData::reset() {
	lastMouseButtonStates[0] = false;
	lastMouseButtonStates[1] = false;
	lastMouseButtonStates[2] = false;
	lastMousePositionX = 0;
	lastMousePositionY = 0;
	lastCollisionCheckResult = false;
	isActive = false;
}


