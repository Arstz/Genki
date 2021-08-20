#pragma once
#include "Window.h"
#include "Shape.h"
#include "ShapeGroup.h"
#include "Vector2f.h"
#include "Shader.h"
#include <list>

#define VERTEX_SIZE 6ul
#define VERTEX_ATTRIB_ARRAY_1 0
#define VERTEX_ATTRIB_ARRAY_2 1

class ShapeController {
private:
	Shader* shader;

	GLuint* additionalBuffers;
	void** additionalBuffersData;
	std::vector<BufferProperties> bufferProperties;
	int bufferCount;

	float* cameraBufferData;

	GLuint VBO;
	GLuint VAO;
	GLuint EBO;

	uint EBOsize;
	uint vertexCount;

	uint* EBObuffer;
	float* vertexBuffer;	

	ShapeGroup shapeGroup;

	static GLFWwindow* window;

	void updateBuffers();
	void reallocateBuffers();
	void initBuffers(void** buffersData);
		

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

	int checkCameraBufferData();

	ShapeController(Shader* shader, void** BuffersData);
	ShapeController& operator=(const ShapeController& shapeController) = delete;
	ShapeController(const ShapeController& shapeController) = delete;
	~ShapeController();
};

