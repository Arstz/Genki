#pragma once
#include "ShapeGroup.h"

class GUIobject {
protected:
	float positionX;
	float positionY;
	ShapeGroup shapeGroup;
	virtual ~GUIobject();
	GUIobject(float positionX, float positionY, ShapeGroup shapeGroup);
public:
	ShapeGroup getShapeGroup();
};

class GUIinteractiveObject : public GUIobject {
public:	
	virtual bool interact(bool mouseButtonStates[3], float x, float y) = 0;
	GUIinteractiveObject(
		float positionX, 
		float positionY, 
		ShapeGroup shapeGroup,
		float LeftBorderX,
		float RightBorderX,
		float UpBorderY,
		float BottomBorderY
	);
protected:
	float LeftBorderX;
	float RightBorderX;
	float UpBorderY;
	float BottomBorderY;
	bool checkCollision(float x, float y);
};

class ButtonSex : public GUIinteractiveObject {
public:
	bool state;
	bool interact(bool mouseButtonStates[3], float x, float y) override;
	ButtonSex(
		float positionX,
		float positionY,
		ShapeGroup shapeGroup,
		float LeftBorderX,
		float RightBorderX,
		float UpBorderY,
		float BottomBorderY
	);
};


class CheckBox : public GUIinteractiveObject {
public:
	bool* state;
};

