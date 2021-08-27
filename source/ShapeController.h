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

	GLuint* additionalBuffers {nullptr};
	void** additionalBuffersData {nullptr};
	std::vector<BufferProperties> bufferProperties;
	int bufferCount;

	float* cameraBufferData {nullptr};

	GLuint	VBO {0};
	GLuint	VAO {0};
	GLuint	EBO {0};

	uint	EBOsize {0};
	uint	vertexCount {0};

	uint*	EBObuffer {nullptr};
	float*	vertexBuffer {nullptr};	

	ShapeGroup shapeGroup {ShapeGroup(0, nullptr, 1.f, 0.f, 0.f, 0)};

	static GLFWwindow* window;

	void updateBuffers();
	void reallocateBuffers();
	void initBuffers(void** buffersData);
		

	void writeToVertexbuffer(
		const ShapeGroup& shapeGroup,
		uint& positionOffsetCounter,
		uint& colorOffsetCounter,
		float alphaChannel,
		float positionX,
		float positionY
	);
	void writeToEBObuffer(
		const ShapeGroup& shapeGroup,
		uint& EBOoffsetCounter,
		uint& vertexCounter
	);

public:
	void destroy();
	void draw();
	void reset();
	
	static void setWindow(GLFWwindow* window);
	void removeShapeGroup(std::list<ShapeGroup>::iterator shapeIterator);

	float* getCameraValuePointer(uint valueNum);

	std::list<ShapeGroup>::iterator addShapeGroup(const ShapeGroup& shapeGroup);
	std::list<ShapeGroup>::iterator addShapeGroup(
		const ShapeGroup& shapeGroup, 
		const std::list<ShapeGroup>::iterator& shapeGroupIterator
	);

	Vector2f screenCoordsToEngineCoords(Vector2f vector) const;
	Vector2f engineCoordsToScreenCoords(Vector2f vector) const;

	Vector2f pxToValue(Vector2f px) const;
	Vector2f valueToPx(Vector2f value) const;

	int checkCameraBufferData();
	ShapeController() = delete;
	ShapeController(Shader* shader, void** BuffersData);
	ShapeController& operator=(const ShapeController& shapeController) = delete;
	ShapeController(const ShapeController& shapeController) = delete;
	~ShapeController();
};

