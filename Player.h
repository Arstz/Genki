#pragma once
#include "Shape.h"
#include "GL\glew.h"
#include "GLFW/glfw3.h"

class Player {
	float* positionX;
	float* positionY;
public:
	int lastDirectionX;
	int lastDirectionY;

	void move(float dx, float dy);

	void setTarget(float* positionX, float* positionY);
};

