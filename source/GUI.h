#pragma once
#include "ShapeGroup.h"
#include "ShapeController.h"
#include "Color.h"

class GUIobject {
protected:
	ShapeController* shapeController;
	std::list<ShapeGroup>::iterator shapeGroup;

public:
	std::list<ShapeGroup>::iterator getShapeGroup();
	virtual ~GUIobject();
	GUIobject();
	GUIobject(const ShapeGroup& shapeGroup, ShapeController* shapeController);
	GUIobject(
		std::list<ShapeGroup>::iterator shapeGroup, ShapeController* shapeController
	);
};

class GUIinteractiveObject : public GUIobject {
	struct InteractionData {
		bool lastMouseButtonStates[3];
		bool lastMousePositionX;
		bool lastMousePositionY;
		bool lastCollisionCheckResult;
		//slider
		bool isActive;
		void reset();

	};
public:	
	void setBorders(int shapeID);
	static void resetInteratiocData();
	static InteractionData interactionData;
	GUIinteractiveObject();
	GUIinteractiveObject(
		ShapeGroup& shapeGroup,
		ShapeController* shapeController
	);
	GUIinteractiveObject(
		ShapeGroup&& shapeGroup, // ( & _ & )
		ShapeController* shapeController, 
		int shapeID
	);
	GUIinteractiveObject(
		std::list<ShapeGroup>::iterator shapeGroup,
		ShapeController* shapeController, 
		int shapeID
	);
	bool checkCollision(float x, float y);
	virtual bool interact(bool mouseButtonStates[3], float x, float y);
protected:
	float LeftBorderX;
	float RightBorderX;
	float UpBorderY;
	float BottomBorderY;
};

class ButtonSex : public GUIinteractiveObject {
public:
	bool state;
	bool interact(bool mouseButtonStates[3], float x, float y) override;
	ButtonSex(Vector2f position, Vector2f size, ShapeController* shapeController);
};

class Button : public GUIinteractiveObject {
public:
	bool state;
	Button(ShapeGroup& shapeGroup, ShapeController* shapeController);
};

class CheckBox : public GUIinteractiveObject {
public:
	bool* state;
	CheckBox(Vector2f position, Vector2f size, ShapeController* shapeController, bool* value);
	bool interact(bool mouseButtonStates[3], float x, float y);
};

class Slider : public GUIinteractiveObject {
protected:
	float* valueX; 
	float* valueY;
	float cursorSize;
	Vector2f min;
	Vector2f max;
	Vector2f position;
	Vector2f size;
	Color activeColor;
	Color passiveColor;
	GUIinteractiveObject cursor;
public:
	Slider(
		Vector2f position,
		Vector2f size,
		float* x,
		float* y,
		Vector2f min,
		Vector2f max,
		ShapeController* shapeController,
		float cursorSize = 0.5
	);  
	bool interact(bool mouseButtonStates[3], float x, float y) override;
};
