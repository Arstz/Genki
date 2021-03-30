#pragma once
#include "Shape.h"
#include "GL\glew.h"
#include "GLFW/glfw3.h"

class Player {
public:
	int lastDirectionX;
	int lastDirectionY;

	float* positionX;
	float* positionY;

	Shape* shape;
	void move(float dx, float dy);
	void bind(Shape* shape);

	void setTarget(float* positionX, float* positionY);
};

