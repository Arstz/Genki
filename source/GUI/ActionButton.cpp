#include "GUI.h"
#include "../Vector2f.h"
#include "../ShapeController.h"

ActionButton::ActionButton(
	Vector2f position,
	Vector2f size,
	ShapeController* shapeController, 
	int buttonIndex,
	std::vector<int>* activatedButtonIDs,
	Color activeColor,
	Color passiveColor
) : GUIinteractiveObject(
		ShapeGroup(1, (Shape*)std::begin(std::initializer_list<Shape> {
		std::move(Shape::makeRectangle(
			Vector2f(0, 0),
			size,
			Vector2f(0, 0),
			passiveColor
		)),

		}),
		1.f,
		position.x,
		position.y,
		0
		),
		shapeController,
		0
	),
	buttonIndex		{buttonIndex},
	position		{position},
	size			{size},
	activeColor		{activeColor},
	passiveColor	{passiveColor},
	activatedButtonIDs {activatedButtonIDs}
{}

bool ActionButton::interact(bool mouseButtonStates[3], float x, float y) {
	if (checkCollision(x, y)) {
		if (mouseButtonStates[0]) {
			if (!interactionData.isActive) {
				interactionData.isActive = true;
				shapeGroup->getShapesPointer()[0].setColor(activeColor);
			}
		}
		else {
			if (interactionData.isActive) {
				activatedButtonIDs->push_back(buttonIndex);
				shapeGroup->getShapesPointer()[0].setColor(passiveColor);
				return false;
			}
			interactionData.isActive = false;
			shapeGroup->getShapesPointer()[0].setColor(passiveColor);
		}
		return true;
	}
	else {
		shapeGroup->getShapesPointer()[0].setColor(passiveColor);
		return false;
	}
}
