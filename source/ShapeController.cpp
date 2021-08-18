#include "ShapeController.h"
#include <iostream>

#include "crtdbg.h"
#include "..\include\CRTDBG\mydbgnew.h"
#ifdef _DEBUG
#define new MYDEBUG_NEW
#endif

GLFWwindow* ShapeController::window = nullptr;

void ShapeController::updateBuffers() {
	uint positionOffsetCounter = 0;
	uint colorOffsetCounter = vertexCount * 2;

	writeToVertexbuffer(shapeGroup, positionOffsetCounter, colorOffsetCounter, 1.f, 0, 0);
}

void ShapeController::writeToVertexbuffer(
	ShapeGroup &shapeGroup,
	uint& positionOffsetCounter,
	uint& colorOffsetCounter,
	float alphaChannel,
	float positionX,
	float positionY
) {
	alphaChannel *= *shapeGroup.getAlphaChannelPointer();
	positionX += *shapeGroup.getPositionXpointer();
	positionY += *shapeGroup.getPositionYpointer();

	Shape* shapes = shapeGroup.getShapesPointer();
	std::list<ShapeGroup>* shapeGroups = shapeGroup.getShapeGroups();

	for (int i = 0; i < shapeGroup.getShapeCount(); i++) {
		float* shapeVertexCoords = shapes[i].getVertexCoordsPointer();
		float* shapeVertexColors = shapes[i].getVertexColorsPointer();

		uint shapeVertexCount = shapes[i].getVertexCount();
		
		for (int j = 0; j < shapeVertexCount * 2; j += 2) {
			vertexBuffer[positionOffsetCounter + j] = shapeVertexCoords[j] + positionX + *shapes[i].getPositionXpointer();
			vertexBuffer[positionOffsetCounter + j + 1] = shapeVertexCoords[j + 1] + positionY + *shapes[i].getPositionYpointer();
		}
		positionOffsetCounter += shapeVertexCount * 2;
		memcpy(&vertexBuffer[colorOffsetCounter], shapeVertexColors, sizeof(*vertexBuffer) * shapeVertexCount * 4);
		for (int j = 3; j < shapeVertexCount * 4; j += 4) {
			vertexBuffer[colorOffsetCounter + j] = shapeVertexColors[j] * (*shapes[i].getAlphaChannelPointer()) * alphaChannel;
		}
		colorOffsetCounter += shapeVertexCount * 4;
	}
	for (auto &shapeGroup : *shapeGroups) {
		writeToVertexbuffer(shapeGroup, positionOffsetCounter, colorOffsetCounter, alphaChannel, positionX, positionY);
	}
}

void ShapeController::writeToEBObuffer(
	ShapeGroup &shapeGroup, 
	uint &EBOoffsetCounter, 
	uint& vertexCounter
) {
	for (int i = 0; i < shapeGroup.getShapeCount(); i++) {
		for (int j = 0; j < shapeGroup.getShapesPointer()[i].getEBOsize(); j++) {
			EBObuffer[EBOoffsetCounter + j] = shapeGroup.getShapesPointer()[i].getVertexIDsPointer()[j] + vertexCounter;
		}
		EBOoffsetCounter += shapeGroup.getShapesPointer()[i].getEBOsize();
		vertexCounter += shapeGroup.getShapesPointer()[i].getVertexCount();
	}
	for (auto& shapeGroup : *shapeGroup.getShapeGroups()) {
		writeToEBObuffer(shapeGroup, EBOoffsetCounter, vertexCounter);
	}
}

void ShapeController::reallocateBuffers() {
	glUseProgram(shader->getGLshaderID());

	free(vertexBuffer);
	vertexBuffer = (float*)malloc(vertexCount * VERTEX_SIZE * sizeof(*vertexBuffer));

	delete[] EBObuffer;
	EBObuffer = (uint*)malloc(sizeof(*EBObuffer) * EBOsize);
	uint EBOoffsetCounter = 0;
	uint vertexCounter = 0;

	writeToEBObuffer(shapeGroup, EBOoffsetCounter, vertexCounter);
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindVertexArray(VAO);
	
	glVertexAttribPointer(
		VERTEX_ATTRIB_ARRAY_2,
		4,
		GL_FLOAT,
		GL_FALSE,
		4 * sizeof(GLfloat),
		(GLvoid*)(2 * vertexCount * sizeof(*vertexBuffer))
	);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(*EBObuffer) * EBOsize, EBObuffer, GL_STATIC_DRAW);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void ShapeController::initBuffers(void** buffersData) {
	vertexCount = 0;
	vertexBuffer = (float*)malloc(0);

	EBOsize = 0;
	EBObuffer = (uint*)malloc(0);

	additionalBuffers = new GLuint[bufferCount];
	additionalBuffersData = new void* [bufferCount];

	for (int i = 0; i < bufferCount; i++) {
		additionalBuffers[i] = 0;
		additionalBuffersData[i] = malloc(bufferProperties[i].bufferSize);
		memcpy(additionalBuffersData[i], buffersData[i], bufferProperties[i].bufferSize);
		glGenBuffers(1, &additionalBuffers[i]);
		glBindBuffer(bufferProperties[i].type, additionalBuffers[i]);
		glBufferData(
			bufferProperties[i].type,
			bufferProperties[i].bufferSize,
			additionalBuffersData[i],
			GL_STATIC_DRAW
		);
	}

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glGenBuffers(1, &EBO);

	glGenVertexArrays(1, &VAO);
	
	glBindVertexArray(VAO);
	glEnableVertexAttribArray(VERTEX_ATTRIB_ARRAY_1);
	glEnableVertexAttribArray(VERTEX_ATTRIB_ARRAY_2);
	glVertexAttribPointer(
		VERTEX_ATTRIB_ARRAY_1,
		2,
		GL_FLOAT,
		GL_FALSE,
		2 * sizeof(GLfloat),
		(GLvoid*)0

	);
	glVertexAttribPointer(
		VERTEX_ATTRIB_ARRAY_2,
		4,
		GL_FLOAT,
		GL_FALSE,
		4 * sizeof(GLfloat),
		(GLvoid*)0
	);
	glDisableVertexAttribArray(VERTEX_ATTRIB_ARRAY_1);
	glDisableVertexAttribArray(VERTEX_ATTRIB_ARRAY_2);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void ShapeController::destroy()
{
	shapeGroup.~ShapeGroup();
}

float* ShapeController::getCameraValuePointer(uint valueNum) {
	return &cameraDataBuffer[valueNum];
}

void ShapeController::draw() {
	glUseProgram(shader->getGLshaderID());
	updateBuffers();

	for (int i = 0; i < bufferCount; i++) {
		glBindBufferBase(
			bufferProperties[i].type, 
			bufferProperties[i].shaderVariableID, 
			additionalBuffers[i]
		);
	}
	glBindBufferBase(
		GL_UNIFORM_BUFFER,
		1,
		CDB
	);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindVertexArray(VAO);

	glEnableVertexAttribArray(VERTEX_ATTRIB_ARRAY_1);
	glEnableVertexAttribArray(VERTEX_ATTRIB_ARRAY_2);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glBufferData(
		GL_UNIFORM_BUFFER,
		sizeof(float) * CAMERA_DATA_SIZE,
		cameraDataBuffer,
		GL_STREAM_DRAW
	);

	glBufferData(
		GL_ARRAY_BUFFER,
		sizeof(float) * vertexCount * VERTEX_SIZE,
		vertexBuffer,
		GL_STREAM_DRAW
	);
	
	glDrawElements(GL_TRIANGLES, EBOsize, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(VERTEX_ATTRIB_ARRAY_1);
	glDisableVertexAttribArray(VERTEX_ATTRIB_ARRAY_2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	glBindVertexArray(0);

}

std::list<ShapeGroup>::iterator ShapeController::addShapeGroup(const ShapeGroup& shapeGroup) {
	vertexCount += shapeGroup.getVertexCount();
	EBOsize += shapeGroup.getEBOsize();
	std::list<ShapeGroup>::iterator otherShapeGroupIterator = ShapeController::shapeGroup.addShapeGroup(shapeGroup);
	reallocateBuffers();
	return otherShapeGroupIterator;
}

std::list<ShapeGroup>::iterator ShapeController::addShapeGroup(
	const ShapeGroup& shapeGroup, 
	const std::list<ShapeGroup>::iterator& shapeGroupIterator
) {
	vertexCount += shapeGroup.getVertexCount();
	EBOsize += shapeGroup.getEBOsize();
	std::list<ShapeGroup>::iterator otherShapeGroupIterator = (*shapeGroupIterator).addShapeGroup(shapeGroup);
	reallocateBuffers();
	return otherShapeGroupIterator;
}

Vector2f ShapeController::screenCoordsToEngineCoords(Vector2f vector) {
	return Vector2f(
		(vector.x * 2 / Window::getWidth() - 1) / cameraDataBuffer[0],
		-(vector.y * 2 / Window::getHeight() - 1) / cameraDataBuffer[1]
	);
}

Vector2f ShapeController::engineCoordsToScreenCoords(Vector2f vector)
{
	return Vector2f(
		Window::getWidth() / 2  * (1 + vector.x * cameraDataBuffer[0]),
		Window::getHeight() / 2  * (1 - vector.y * cameraDataBuffer[1])
	);
}

Vector2f ShapeController::pxToValue(Vector2f px) {
	return Vector2f(
		px.x * 2 / Window::getWidth() / cameraDataBuffer[0],
		px.y * 2 / Window::getHeight() / cameraDataBuffer[1]
	);
}
 
Vector2f ShapeController::valueToPx(Vector2f value) {
	return Vector2f(
		Window::getWidth() / 2 * value.x * cameraDataBuffer[0],
		Window::getHeight() / 2 * value.y * cameraDataBuffer[1]
	);
}

void ShapeController::setWindow(GLFWwindow* window) {
	ShapeController::window = window;
}

void ShapeController::removeShapeGroup(std::list<ShapeGroup>::iterator& shapeGroupIterator) {
	vertexCount -= (*shapeGroupIterator).getVertexCount();
	EBOsize -= (*shapeGroupIterator).getEBOsize();

	shapeGroup.removeShapeGroup(shapeGroupIterator);
	reallocateBuffers();
}

ShapeController::ShapeController(Shader* shader, void** buffersData) {
	this->shapeGroup = ShapeGroup(0, nullptr, 1.f, 0.f, 0.f, 0);
	this->shader = shader;
	this->bufferProperties = shader->getBufferProperties();
	this->bufferCount = bufferProperties.size();

	glUseProgram(shader->getGLshaderID());

	this->cameraDataBuffer[0] = 0.1f / 16.f * 9.f;
	this->cameraDataBuffer[1] = 0.1f;

	this->VBO = 0;
	this->VAO = 0;
	this->EBO = 0;
	this->CDB = 0;
		
	if (window) {
		initBuffers(buffersData);
	}
}

ShapeController::~ShapeController() {
	free(EBObuffer);
	free(vertexBuffer);
	this->vertexBuffer = nullptr;
	this->EBObuffer = nullptr;

	if (window) {
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
		glDeleteBuffers(1, &CDB);
		for (int i = 0; i < bufferCount; i++) {
			free(additionalBuffersData[i]);
			additionalBuffersData[i] = nullptr;
			glDeleteBuffers(1, (const GLuint*)additionalBuffers[i]);
		}
		additionalBuffersData = nullptr;
	}
}

