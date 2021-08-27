#pragma once
#include "../ShapeGroup.h"

#include "../ShapeController.h"
#include "../Color.h"
#define REQUEST_DATA_SIZE 17

enum class RequestType {
	NONE,
	RESIZE
};

class GUIobject {
protected:
	ShapeController* shapeController;
	std::list<ShapeGroup>::iterator shapeGroup;
	void virtual processRequest(RequestType request, char data[REQUEST_DATA_SIZE]);

public:
	std::list<ShapeGroup>::iterator getShapeGroup();
	virtual ~GUIobject() = default;
	GUIobject() = delete;
	GUIobject(const GUIobject& other) = delete;
	GUIobject& operator=(const GUIobject& other) = delete;
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
protected:
	float LeftBorderX;
	float RightBorderX;
	float UpBorderY;
	float BottomBorderY;

public:	
	void setBorders(int shapeID);
	static void resetInterationData();
	static InteractionData interactionData;

	~GUIinteractiveObject() = default;
	GUIinteractiveObject() = delete;
	GUIinteractiveObject(const GUIinteractiveObject& other) = delete;
	GUIinteractiveObject& operator=(const GUIinteractiveObject& other) = delete;

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

};

class ButtonSex : public GUIinteractiveObject {
public:
	ButtonSex() = delete;
	bool state;
	bool interact(bool mouseButtonStates[3], float x, float y) override;
	ButtonSex(Vector2f position, Vector2f size, ShapeController* shapeController);
};

class CheckBox : public GUIinteractiveObject {
	bool* state;
public:
	CheckBox() = delete;
	CheckBox(const CheckBox& other) = delete;
	CheckBox& operator=(const CheckBox& other) = delete;
	CheckBox(Vector2f position, Vector2f size, ShapeController* shapeController, bool* value);
	bool interact(bool mouseButtonStates[3], float x, float y) override;
};

class Slider : public GUIinteractiveObject {
	float*		valueX; 
	float*		valueY;
	float		cursorSize;
	Vector2f	min;
	Vector2f	max;
	Vector2f	position;
	Vector2f	size;
	Color		activeColor;
	Color		passiveColor;
	GUIinteractiveObject cursor;
public:
	Slider() = delete;
	Slider(const Slider& other) = delete;
	Slider& operator=(const Slider& other) = delete;
	Slider(
		Vector2f position,
		Vector2f size,
		float* x,
		float* y,
		Vector2f min,
		Vector2f max,
		ShapeController* shapeController,
		float cursorSize = 0.05
	);
	bool interact(bool mouseButtonStates[3], float x, float y) override;
};

class GUIcontainer : public GUIinteractiveObject {
	Slider	slider;
	int		objectCount;
	float*	objectHeights;
	GUIinteractiveObject* objects; 
public:
	GUIcontainer() = delete;
	GUIcontainer(const GUIcontainer& other) = delete;
	GUIcontainer& operator=(const GUIcontainer& other) = delete;
	void virtual processRequest(RequestType request, char data[REQUEST_DATA_SIZE]) override;
};

class ActionButton : public GUIinteractiveObject {
	int			buttonIndex;
	Vector2f	position;
	Vector2f	size;
	Color		activeColor;
	Color		passiveColor;
	std::vector<int>* activatedButtonIDs;
public:
	ActionButton() = delete;
	ActionButton(const ActionButton& other) = delete;
	ActionButton& operator=(const ActionButton& other) = delete;
	ActionButton(
		Vector2f position,
		Vector2f size,
		ShapeController* shapeController,
		int buttonIndex,
		std::vector<int>* activatedButtonIDs,
		Color activeColor,
		Color passiveColor
	);
	bool interact(bool mouseButtonStates[3], float x, float y) override;
};
