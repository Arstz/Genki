#pragma once
#include "Window.h"
#include "Shape.h"
#include <list>

#define VERTEX_SIZE 6ul
#define CAMERA_DATA_SIZE 4u

class ShapeController {
public:
	static std::list<Shape*> shapes;

	static uint vertexCount;
	static float* vertexDataBuffer;

	static GLuint bufferID;

	static uint EBOsize;
	static uint* EBObuffer;
	static float cameraDataBuffer[4];

	static GLuint VBO;
	static GLuint VAO;
	static GLuint EBO;
	static GLuint CDB;

	static GLFWwindow* window;
	static int shader;

	static void updateBuffers();
	static void reallocateBuffers();
	static void setWindow(GLFWwindow* window);
	static void initBuffers();
	static void initShader();
	static void init();
	static float* getCameraValuePointer(uint valueNum);
	static void draw();
	static std::list<Shape*>::iterator addShape(Shape* shape);
	static void removeShape(std::list<Shape*>::iterator& shapeIterator);

};

