#pragma once
#include "Window.h"
#include "Shape.h"
#include "ShapeGroup.h"
#include <list>

#define VERTEX_SIZE 6ul
#define CAMERA_DATA_SIZE 4u

class ShapeController {
private:
	int shader;

	GLuint bufferID;
	GLuint VBO;
	GLuint VAO;
	GLuint EBO;
	GLuint CDB;

	uint EBOsize;
	uint vertexCount;

	uint* EBObuffer;

	float cameraDataBuffer[4];

	float* vertexBuffer;	

	ShapeGroup shapeGroup;

	GLFWwindow* window;

	void updateBuffers();
	void reallocateBuffers();
	void initBuffers();
	void initShader();		

	void writeToVertexbuffer(
		ShapeGroup& shapeGroup,
		uint& positionOffsetCounter,
		uint& colorOffsetCounter,
		float alphaChannel,
		float positionX,
		float positionY
	);
	void writeToEBObuffer(
		ShapeGroup& shapeGroup,
		uint& EBOoffsetCounter,
		uint& vertexCounter
	);

public:
	void destroy();
	void draw();
	
	void removeShapeGroup(std::list<ShapeGroup>::iterator& shapeIterator);

	float* getCameraValuePointer(uint valueNum);

	std::list<ShapeGroup>::iterator addShapeGroup(const ShapeGroup& shapeGroup);
	std::list<ShapeGroup>::iterator addShapeGroup(
		const ShapeGroup& shapeGroup, 
		const std::list<ShapeGroup>::iterator& shapeGroupIterator
	);

	ShapeController();
	ShapeController& operator=(const ShapeController& shapeController);
	ShapeController(const ShapeController& shapeController);
	ShapeController(GLFWwindow* window);
	~ShapeController();
};

