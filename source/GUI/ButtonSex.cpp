#define AAA (float)rand()/(float)RAND_MAX

#include <iostream>

#include "GUI.h"
#include "../Vector2f.h"
#include "../ShapeController.h"
#include "../Text.h"
#include "../GUIcanvas.h"

bool ButtonSex::interact(bool mouseButtonStates[3], float x, float y) {
	if (!state && checkCollision(x, y) && mouseButtonStates[0]) {
		std::cout << "sex\n";
		for (int i = 0; i < 100; i++) {
			Text::setColor(Color(AAA, AAA, AAA, AAA));
			Text::setScale(Vector2f(AAA / 50, AAA / 50));
//			this->shapeController->addShapeGroup(Text::makeText("SECKS", Vector2f((AAA - 0.5f) * 2, (AAA - 0.5f) * 2)));
			std::list<GUIobject*>::iterator ok = GUIcanvas::addGUIobject(Text::makeText("SECKS", Vector2f((AAA - 0.5f) * 2, (AAA - 0.5f) * 2)));
		}
		this->state = true;
	}
	if (!mouseButtonStates[0]) {
		this->state = false;
		return false;
	}

	return true;
}

ButtonSex::ButtonSex(
	Vector2f position, 
	Vector2f size, 
	ShapeController* shapeController
) : GUIinteractiveObject(
		ShapeGroup(1, (Shape*)std::begin(std::initializer_list<Shape> {
				std::move(Shape::makeRectangle(
					Vector2f(0, 0),
					size,
					Vector2f(0, 0),
					Color(1.f, 1.f, 0.f, 1.f)
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
	state{false}
{}
