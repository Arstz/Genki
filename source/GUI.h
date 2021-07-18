#pragma once
#include "ShapeGroup.h"

enum class ButtonType 
{
	EMPTY,
	BUTTON_SEX,
	BUTTON,
	SLIDER
};

class GUIobject {
protected:
	ShapeGroup shapeGroup;
	virtual ~GUIobject();
	GUIobject(ShapeGroup shapeGroup);
public:
	ShapeGroup getShapeGroup();
};

class GUIinteractiveObject : public GUIobject {
public:	
	GUIinteractiveObject();
	GUIinteractiveObject(
		float positionX, 
		float positionY, 
		ShapeGroup shapeGroup,
		float LeftBorderX,
		float RightBorderX,
		float UpBorderY,
		float BottomBorderY
	);
	virtual ButtonType getType();
	bool checkCollision(float x, float y);
protected:
	float LeftBorderX;
	float RightBorderX;
	float UpBorderY;
	float BottomBorderY;
};

class ButtonSex : public GUIinteractiveObject {
public:
	bool state;
	ButtonType getType() override;
	ButtonSex(ShapeGroup shapeGroup);
};

class Button : public GUIinteractiveObject {
public:
	bool state;
	ButtonType getType() override;
	Button(ShapeGroup shapeGroup);
};

class CheckBox : public GUIinteractiveObject {
public:
	bool* state;
};

class Slider : public GUIinteractiveObject {
public:
	bool state;
	float* cursorPointerX;
	float* cursorPointerY;
	ButtonType getType() override;
	Slider(ShapeGroup shapeGroup);
};

