#pragma once
#include "ShapeGroup.h"

class GUIobject
{
protected:
	float positionX;
	float positionY;
	ShapeGroup shapeGroup;
};

class GUIinteractiveObject : public GUIobject
{
public:	
	virtual bool interact(bool mouseButtonStates[3], float x, float y) = 0;
protected:
	float LeftBorderX;
	float RightBorderX;
	float UpBorderY;
	float BottomBorderY;
	bool checkCollision(float x, float y);
};

class CheckBox : public GUIinteractiveObject
{
public:
	bool* state;
};

