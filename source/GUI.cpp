#include "GUI.h"
#include <iostream>

#include "crtdbg.h"
#include "..\include\CRTDBG\mydbgnew.h"
#ifdef _DEBUG
#define new MYDEBUG_NEW
#endif

GUIinteractiveObject::GUIinteractiveObject(
	float positionX,
	float positionY,
	ShapeGroup shapeGroup,
	float LeftBorderX,
	float RightBorderX,
	float UpBorderY,
	float BottomBorderY
) : GUIobject(positionX, positionY, shapeGroup) {
	this->LeftBorderX	= LeftBorderX;
	this->RightBorderX	= RightBorderX;
	this->UpBorderY		= UpBorderY;
	this->BottomBorderY	= BottomBorderY;

}

bool GUIinteractiveObject::checkCollision(float x, float y){
	return x < RightBorderX && x > LeftBorderX && y > UpBorderY && y < BottomBorderY;
}

GUIobject::~GUIobject() {}

GUIobject::GUIobject(float positionX, float positionY, ShapeGroup shapeGroup) {
	this->positionX = positionX;
	this->positionY = positionY;
	this->shapeGroup = shapeGroup;
}

ShapeGroup GUIobject::getShapeGroup() {
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

ButtonSex::ButtonSex(
	float positionX,
	float positionY,
	ShapeGroup shapeGroup,
	float LeftBorderX,
	float RightBorderX,
	float UpBorderY,
	float BottomBorderY
): GUIinteractiveObject(
	positionX,
	positionY,
	shapeGroup,
	LeftBorderX,
	RightBorderX,
	UpBorderY,
	BottomBorderY
) {
	this->state = false;
}
