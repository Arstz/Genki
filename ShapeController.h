#pragma once
#include "Window.h"
#include "Shape.h"
#include "ShapeGroup.h"
#include <list>

#define VERTEX_SIZE 6ul
#define CAMERA_DATA_SIZE 4u

class ShapeController {
	static std::list<ShapeGroup*> shapeGroups;

	static uint vertexCount;
	static float* vertexBuffer;

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

	static void initBuffers();
	static void initShader();
public:

	static void setWindow(GLFWwindow* window);

	static void init();
	static float* getCameraValuePointer(uint valueNum);
	static void draw();
	static std::list<ShapeGroup*>::iterator addShape(Shape* shape);
	static std::list<ShapeGroup*>::iterator addShapeGroup(ShapeGroup* shapeGroup);
	static void removeShapeGroup(std::list<ShapeGroup*>::iterator& shapeIterator);

	static void writeToVertexbuffer(
		ShapeGroup* shapeGroup, 
		uint& positionOffsetCounter, 
		uint& colorOffsetCounter,
		float positionX,
		float positionY
	);

	static void writeToEBObuffer(ShapeGroup* shapeGroup, uint &EBOoffsetCounter);
};

