#pragma once
#include "ShapeGroup.h"
#include "ShapeController.h"

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
	static InteractionData interactionData;
	GUIinteractiveObject() = delete;
	GUIinteractiveObject(
		ShapeGroup& shapeGroup,
		ShapeController* shapeController
	);
	bool checkCollision(float x, float y);
	virtual bool interact(bool mouseButtonStates[3], float x, float y) = 0;
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
	ButtonSex(ShapeGroup&& shapeGroup, ShapeController* shapeController);
};

class Button : public GUIinteractiveObject {
public:
	bool state;
	Button(ShapeGroup& shapeGroup, ShapeController* shapeController);
};

class CheckBox : public GUIinteractiveObject {
public:
	bool* state;
};

class Slider : public GUIinteractiveObject {
public:
	float minX;
	float maxX;
	float* x;
	float minY;
	float maxY;
	float* y;
	Slider(ShapeGroup&& shapeGroup, ShapeController* shapeController);
	bool interact(bool mouseButtonStates[3], float x, float y) override;
};

