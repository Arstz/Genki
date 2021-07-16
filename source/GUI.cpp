#include "crtdbg.h"
#include "..\include\CRTDBG\mydbgnew.h"

#include <iostream>
#include "GUI.h"
#include "Window.h"
#ifdef _DEBUG
#define new MYDEBUG_NEW
#endif

GUIinteractiveObject::GUIinteractiveObject(ShapeGroup shapeGroup) : GUIobject(shapeGroup)
{
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

GUIinteractiveObject::GUIinteractiveObject(
	float positionX,
	float positionY,
	ShapeGroup shapeGroup,
	float LeftBorderX,
	float RightBorderX,
	float UpBorderY,
	float BottomBorderY
) : GUIobject(shapeGroup) {
	this->LeftBorderX	= LeftBorderX;
	this->RightBorderX	= RightBorderX;
	this->UpBorderY		= UpBorderY;
	this->BottomBorderY	= BottomBorderY;

}

ButtonType GUIinteractiveObject::getType()
{
	return ButtonType();
}

bool GUIinteractiveObject::checkCollision(float x, float y){
	//std::cout << x <<'\t' << y << std::endl;
	return x < RightBorderX && x > LeftBorderX && y > UpBorderY && y < BottomBorderY;
}

GUIobject::~GUIobject() {}

GUIobject::GUIobject(ShapeGroup shapeGroup) {
	this->shapeGroup = shapeGroup;
}

ShapeGroup GUIobject::getShapeGroup() {
	return shapeGroup;
}

ButtonType ButtonSex::getType()
{
	return ButtonType::BUTTON_SEX;
}

ButtonSex::ButtonSex(ShapeGroup shapeGroup) : GUIinteractiveObject(shapeGroup) {
	this->state = false;
}

ButtonType Button::getType()
{
	return ButtonType::BUTTON;
}

Button::Button(ShapeGroup shapeGroup) : GUIinteractiveObject(shapeGroup) {
	this->state = false;
}
