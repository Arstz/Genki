#pragma once
#include "Shape.h"
#include "ShapeGroup.h"
#include <string>
#include "Vector2f.h"
#include "Color.h"

class Text {
	static const Shape symbols[256];
	static const float symbolLengths[256];
	static float spacingLength;
	static Vector2f scale;
	static Color color;
public:
	static void setColor(Color color);
	static void setScale(Vector2f scale);

	static ShapeGroup makeText(std::string text, Vector2f position);

};

