#include "GUI.h"
#include "../Vector2f.h"
#include "../ShapeController.h"

CheckBox::CheckBox(
	Vector2f position,
	Vector2f size,
	ShapeController* shapeController,
	bool* value
) : GUIinteractiveObject(
		std::move(ShapeGroup(
			2,
			+
			(Shape*)std::begin(std::initializer_list<Shape> {
				std::move(Shape::makeRectangle(Vector2f(0, 0), Vector2f(size.x, size.y), Vector2f(0, 0), Color(0, 0, 0, 1.f), 0)),
				std::move(Shape::makeRectangle(Vector2f(-size.x / 3, -size.y / 3), Vector2f(size.x / 3, size.y / 3), Vector2f(size.x / 2, size.y / 2), *value ? Color(1, 0, 0, 1) : Color(0, 0, 0, 0), 1))
			}),
			1.f,
			position.x,
			position.y,
			0
		)),
		shapeController,
		0
	),
	state {value}
{}

bool CheckBox::interact(bool mouseButtonStates[3], float x, float y) {
	if (checkCollision(x, y)) {
		shapeGroup->getShapesPointer()[0].setColor(Color(0.5, 0.5, 0.5, 1));
		if (mouseButtonStates[0]) {	
			if (!interactionData.isActive) {
				interactionData.isActive = true;
				*state = !*state;
			}			
			if (*state) {
				shapeGroup->getShapesPointer()[1].setColor(Color(1, 0, 0, 1));				
			}
			else {
				shapeGroup->getShapesPointer()[1].setColor(Color(1, 0, 0, 0));
			}
		}
		else {
			interactionData.isActive = false;
		}
		return true;
	}
	else {
		shapeGroup->getShapesPointer()[0].setColor(Color(0, 0, 0, 1));
		return false;
	}
}