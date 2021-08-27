#include "GUI.h"
#include "../Vector2f.h"
#include "../ShapeController.h"

Slider::Slider(
	Vector2f position,
	Vector2f size,
	float* valueX,
	float* valueY,
	Vector2f min,
	Vector2f max,
	ShapeController* shapeController,
	float cursorSize
) : GUIinteractiveObject(	
		std::move(ShapeGroup(
			2,
			(Shape*)std::begin(std::initializer_list<Shape> {
				std::move(Shape::makeRectangle(Vector2f(0, 0), Vector2f(std::max(size.x, cursorSize), std::max(size.y, cursorSize)), Vector2f(0, 0), Color(0.5, 0.5, 0.5, 1.f), 0)),
				std::move(Shape::makeRectangle(Vector2f(-cursorSize /2, -cursorSize / 2), Vector2f(cursorSize / 2, cursorSize / 2), Vector2f(cursorSize / 2, cursorSize / 2), Color(0, 0, 0, 1), 1))
			}),
			1.f,
			position.x,
			position.y,
			0
		)),
		shapeController, 
		0
	),
	cursor		{shapeGroup, shapeController, 1},
	size		{Vector2f(std::max(size.x, cursorSize), std::max(size.y, cursorSize))},
	valueX		{valueX},
	valueY		{valueY},
	min			{min},
	max			{max},
	cursorSize	{cursorSize},
	position	{position}
{}

bool Slider::interact(bool mouseButtonStates[3], float x, float y) {
	if (interactionData.isActive) { //If in last frame cursor was active
		if (mouseButtonStates[0]) {
			update:
			Vector2f pos(x, y);
			Vector2f cursorSizePx(shapeController->valueToPx(Vector2f(cursorSize / 2, cursorSize / 2)));
			pos.x = std::max(pos.x, LeftBorderX + cursorSizePx.x); //aaaa
			pos.x = std::min(pos.x, RightBorderX - cursorSizePx.x);
			pos.y = std::min(pos.y, BottomBorderY - cursorSizePx.y);
			pos.y = std::max(pos.y, UpBorderY + cursorSizePx.y);

			pos = shapeController->screenCoordsToEngineCoords(pos);

			*shapeGroup->getShapesPointer()[1].getPositionXpointer() = pos.x - *shapeGroup->getPositionXpointer();
			*shapeGroup->getShapesPointer()[1].getPositionYpointer() = pos.y - *shapeGroup->getPositionYpointer();

			*valueX = (pos.x - position.x - cursorSize) / (size.x - cursorSize) * (max.x - min.x) + min.x;
			*valueY = (pos.y - position.y - cursorSize) / (size.y - cursorSize) * (max.y - min.y) + min.y;
		} else {			
			if (checkCollision(x, y)) {
				interactionData.isActive = false;	
				shapeGroup->getShapesPointer()[1].setColor(Color(0, 0, 0, 1));
				cursor.setBorders(1);
				if (cursor.checkCollision(x, y)) {
					shapeGroup->getShapesPointer()[1].setColor(Color(1, 1, 1, 1));
					interactionData.lastCollisionCheckResult = true;
				}
				else {
					interactionData.lastCollisionCheckResult = false;
				}
			}
			else {
				cursor.setBorders(1);
				return false; 
			}
		}
	}
	else {
		if (checkCollision(x, y)) {
			if (mouseButtonStates[0]) {
				interactionData.isActive = true;
				shapeGroup->getShapesPointer()[1].setColor(Color(0, 0.5, 1, 1));
				goto update;
			}
			else {
				if (cursor.checkCollision(x, y)) {
					if (!interactionData.lastCollisionCheckResult) {
						shapeGroup->getShapesPointer()[1].setColor(Color(1, 1, 1, 1));
					}
					interactionData.lastCollisionCheckResult = true;
				}
				else if (interactionData.lastCollisionCheckResult == true) {
					interactionData.lastCollisionCheckResult = false;
					shapeGroup->getShapesPointer()[1].setColor(Color(0, 0, 0, 1));
				}
			}
		}
		else {
			shapeGroup->getShapesPointer()[1].setColor(Color(0, 0, 0, 1));
			return false; //If mouse cursor leaves padding area
		}
	}
	return true;
}
