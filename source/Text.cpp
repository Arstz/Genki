#include "Text.h"
#include "Asphlt.h"

Color Text::color = Color(0, 0, 0);
Vector2f Text::scale = Vector2f(1.f, 1.f);
float Text::spacingLength = 1.f;

ShapeGroup Text::makeText(std::string text, Vector2f position) {
	Shape* shapes = new Shape[text.size()];
	float offset = 0;
	for (int i = 0; i < text.size(); i++) {
		shapes[i] = symbols[text[i]];
		*shapes[i].getPositionXpointer() = offset * scale.x;
		shapes[i].scale(scale);
		shapes[i].setColor(color);
		offset += symbolLengths[text[i]] + spacingLength;
	}
    return ShapeGroup(text.size(), shapes, 1.f, position.x, position.y, 0);
}

void Text::setColor(Color color) {
	Text::color = color;
}

void Text::setScale(Vector2f scale) {
	Text::scale = scale;
}

