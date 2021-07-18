#pragma once
#include "ShapeGroup.h"
#include "ShapeController.h"

enum class ButtonType 
{
	EMPTY,
	BUTTON_SEX,
	BUTTON,
	SLIDER
};

class GUIobject {
protected:
	std::list<ShapeGroup>::iterator shapeGroup;
	virtual ~GUIobject();
	GUIobject() = delete;
	GUIobject(const ShapeGroup& shapeGroup, ShapeController* shapeController);
public:
	std::list<ShapeGroup>::iterator getShapeGroup();
};

class GUIinteractiveObject : public GUIobject {
public:	
	GUIinteractiveObject() = delete;
	GUIinteractiveObject(
		ShapeGroup& shapeGroup,
		ShapeController* shapeController
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
	ButtonSex(ShapeGroup&& shapeGroup, ShapeController* shapeController);
};

class Button : public GUIinteractiveObject {
public:
	bool state;
	ButtonType getType() override;
	Button(ShapeGroup& shapeGroup, ShapeController* shapeController);
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
	Slider(ShapeGroup& shapeGroup, ShapeController* shapeController);
};

