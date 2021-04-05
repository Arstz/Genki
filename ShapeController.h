#pragma once
#include "Window.h"
#include "Shape.h"
#include "ShapeGroup.h"
#include <list>

#define VERTEX_SIZE 6ul
#define CAMERA_DATA_SIZE 4u

class ShapeController {
	static int shader;

	static GLuint bufferID;
	static GLuint VBO;
	static GLuint VAO;
	static GLuint EBO;
	static GLuint CDB;

	static uint EBOsize;
	static uint vertexCount;

	static uint* EBObuffer;

	static float cameraDataBuffer[4];

	static float* vertexBuffer;	

	static ShapeGroup shapeGroup;

	static GLFWwindow* window;

	static void updateBuffers();
	static void reallocateBuffers();
	static void initBuffers();
	static void initShader();		

	static void writeToVertexbuffer(
		ShapeGroup& shapeGroup,
		uint& positionOffsetCounter,
		uint& colorOffsetCounter,
		float alphaChannel,
		float positionX,
		float positionY
	);
	static void writeToEBObuffer(
		ShapeGroup& shapeGroup,
		uint& EBOoffsetCounter,
		uint& vertexCounter
	);

public:
	static void destroy();
	static void init();
	static void draw();
	
	static void setWindow(GLFWwindow* window);
	static void removeShapeGroup(std::list<ShapeGroup>::iterator& shapeIterator);

	static float* getCameraValuePointer(uint valueNum);

	static std::list<ShapeGroup>::iterator addShapeGroup(const ShapeGroup& shapeGroup);
	static std::list<ShapeGroup>::iterator addShapeGroup(
		const ShapeGroup& shapeGroup, 
		const std::list<ShapeGroup>::iterator& shapeGroupIterator
	);
	static void terminate();

};

