#pragma once
#include "Window.h"
#include "Shape.h"
#include "ShapeGroup.h"
#include "Vector2f.h"
#include <list>

#define VERTEX_SIZE 6ul
#define CAMERA_DATA_SIZE 2u
#define VERTEX_ATTRIB_ARRAY_1 0
#define VERTEX_ATTRIB_ARRAY_2 1

class ShapeController {
private:
	static int shader;

	GLuint VBO;
	GLuint VAO;
	GLuint EBO;
	GLuint CDB;

	uint EBOsize;
	uint vertexCount;

	uint* EBObuffer;

	float cameraDataBuffer[2];

	float* vertexBuffer;	

	ShapeGroup shapeGroup;

	static GLFWwindow* window;

	void updateBuffers();
	void reallocateBuffers();
	void initBuffers();
		

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
	static void initShader();
	void destroy();
	void draw();
	
	static void setWindow(GLFWwindow* window);
	void removeShapeGroup(std::list<ShapeGroup>::iterator& shapeIterator);

	float* getCameraValuePointer(uint valueNum);

	std::list<ShapeGroup>::iterator addShapeGroup(const ShapeGroup& shapeGroup);
	std::list<ShapeGroup>::iterator addShapeGroup(
		const ShapeGroup& shapeGroup, 
		const std::list<ShapeGroup>::iterator& shapeGroupIterator
	);

	Vector2f screenCoordsToEngineCoords(Vector2f vector);
	Vector2f engineCoordsToScreenCoords(Vector2f vector);

	Vector2f pxToValue(Vector2f px);
	Vector2f valueToPx(Vector2f value);

	ShapeController();
	ShapeController& operator=(const ShapeController& shapeController) = delete;
	ShapeController(const ShapeController& shapeController) = delete;
	~ShapeController();
};

