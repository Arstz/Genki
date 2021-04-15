#include "ShapeController.h"
#include <iostream>

#include "crtdbg.h"
#include "..\include\CRTDBG\mydbgnew.h"
#ifdef _DEBUG
#define new MYDEBUG_NEW
#endif


const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec2 pos;\n"
"layout (location = 1) in vec4 color;\n"

"layout(std140) uniform Camera"
"{"
"	vec2 offset;"
"	vec2 scale;"
"};"
"out vec4 vertexColor;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4((pos-offset)*scale, 0.f, 1.f);\n"
"   vertexColor = color;\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec4 vertexColor;\n"
"void main()\n"
"{\n"
"   FragColor = vertexColor;\n"
"}\n\0";

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
	std::list<ShapeGroup> shapeGroups = shapeGroup.getShapeGroups();

	for (int i = 0; i < shapeGroup.getShapeCount(); i++) {
		float* shapeVertexCoords = shapes[i].getVertexCoordsPointer();
		float* shapeVertexColors = shapes[i].getVertexColorsPointer();

		uint shapeVertexCount = shapes[i].getVertexCount();
		
		for (int j = 0; j < shapeVertexCount * 2; j += 2) {
			vertexBuffer[positionOffsetCounter + j] = shapeVertexCoords[j] + positionX + *shapes[i].getPositionXpointer();
			vertexBuffer[positionOffsetCounter + j + 1] = shapeVertexCoords[j + 1] + positionY + *shapes[i].getPositionYpointer();
		}
		positionOffsetCounter += shapeVertexCount * 2;

		for (int j = 0; j < shapeVertexCount * 4; j += 4) {
			vertexBuffer[colorOffsetCounter + j] = shapeVertexColors[j];
			vertexBuffer[colorOffsetCounter + j + 1] = shapeVertexColors[j + 1];
			vertexBuffer[colorOffsetCounter + j + 2] = shapeVertexColors[j + 2];
			vertexBuffer[colorOffsetCounter + j + 3] = shapeVertexColors[j + 3] * (*shapes[i].getAlphaChannelPointer()) * alphaChannel;
		}
		colorOffsetCounter += shapeVertexCount * 4;
	}
	for (auto &shapeGroup : shapeGroups) {
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
	for (auto& shapeGroup : shapeGroup.getShapeGroups()) {
		writeToEBObuffer(shapeGroup, EBOoffsetCounter, vertexCounter);
	}
}

void ShapeController::reallocateBuffers() {
	free(vertexBuffer);
	vertexBuffer = (float*)malloc(vertexCount * VERTEX_SIZE * sizeof(vertexBuffer));

	delete[] EBObuffer;
	EBObuffer = (uint*)malloc(sizeof(EBObuffer) * EBOsize);
	glBindVertexArray(VAO);
	glVertexAttribPointer(
		1,
		4,
		GL_FLOAT,
		GL_FALSE,
		4 * sizeof(GLfloat),
		(GLvoid*)(2 * vertexCount * sizeof(float)));



	uint EBOoffsetCounter = 0;
	uint vertexCounter = 0;

	writeToEBObuffer(shapeGroup, EBOoffsetCounter, vertexCounter);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * EBOsize, EBObuffer, GL_STATIC_DRAW);
	glBindVertexArray(0);
}

void ShapeController::initBuffers() {
	ShapeController::bufferID = Window::generateBufferID();
	glGenBuffers(bufferID, &CDB);
	glBindBuffer(GL_UNIFORM_BUFFER, CDB);

	glUniformBlockBinding(
		shader,
		glGetUniformBlockIndex(shader, "Camera"),
		1
	);
	glBindBufferBase(GL_UNIFORM_BUFFER, 1, CDB);

	glGenBuffers(bufferID, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glGenVertexArrays(bufferID, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(bufferID, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glVertexAttribPointer(
		0,
		2,
		GL_FLOAT,
		GL_FALSE,
		2 * sizeof(GLfloat),
		(GLvoid*)0
	);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);
}

void ShapeController::initShader() {
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	shader = glCreateProgram();
	glAttachShader(shader, vertexShader);
	glAttachShader(shader, fragmentShader);
	glLinkProgram(shader);

	glGetProgramiv(shader, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void ShapeController::destroy()
{
	shapeGroup.~ShapeGroup();
}

float* ShapeController::getCameraValuePointer(uint valueNum) {
	return &cameraDataBuffer[valueNum];
}

void ShapeController::draw() {
	updateBuffers();

	glBufferData(
		GL_ARRAY_BUFFER,
		sizeof(float) * vertexCount * VERTEX_SIZE,
		vertexBuffer,
		GL_STREAM_DRAW
	);

	glBufferData(
		GL_UNIFORM_BUFFER,
		sizeof(float) * 4,
		cameraDataBuffer,
		GL_STATIC_DRAW
	);

	glUseProgram(shader);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, EBOsize, GL_UNSIGNED_INT, 0);
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

void ShapeController::setWindow(GLFWwindow* window) {
	ShapeController::window = window;
}

void ShapeController::removeShapeGroup(std::list<ShapeGroup>::iterator& shapeGroupIterator) {
	vertexCount -= (*shapeGroupIterator).getVertexCount();
	EBOsize -= (*shapeGroupIterator).getEBOsize();

	shapeGroup.removeShapeGroup(shapeGroupIterator);
	reallocateBuffers();
}

ShapeController::ShapeController() {
	this->shapeGroup = ShapeGroup(0, nullptr, 1.f, 0.f, 0.f, 0);

	this->vertexCount = 0;
	this->vertexBuffer = (float*)malloc(0);

	this->bufferID = 0;

	this->EBOsize = 0;
	this->EBObuffer = (uint*)malloc(0);

	this->cameraDataBuffer[0] = 0.f;
	this->cameraDataBuffer[1] = 0.f;
	this->cameraDataBuffer[2] = 0.1f / 16.f * 9.f;
	this->cameraDataBuffer[3] = 0.1f;

	this->VBO = 0;
	this->VAO = 0;
	this->EBO = 0;
	this->CDB = 0;

	this->shader = 0;

//  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

ShapeController& ShapeController::operator=(const ShapeController& shapeController) {
	free(EBObuffer);
	free(vertexBuffer);

	this->shapeGroup = shapeController.shapeGroup;

	this->vertexCount = shapeController.vertexCount;
	this->vertexBuffer = (float*)malloc(vertexCount * 6);

	this->bufferID = shapeController.bufferID;

	this->EBOsize = shapeController.EBOsize;
	this->EBObuffer = (uint*)malloc(EBOsize);

	this->cameraDataBuffer[0] = 0.f;
	this->cameraDataBuffer[1] = 0.f;
	this->cameraDataBuffer[2] = 0.1f / 16.f * 9.f;
	this->cameraDataBuffer[3] = 0.1f;

	this->VBO = shapeController.VBO;
	this->VAO = shapeController.VAO;
	this->EBO = shapeController.EBO;
	this->CDB = shapeController.CDB;

	this->shader = shapeController.shader;
	
	if (window) {
		initShader();
		initBuffers();
	}
	return *this;
}

ShapeController::ShapeController(const ShapeController& shapeController) {
	this->shapeGroup = shapeController.shapeGroup;

	this->vertexCount = shapeController.vertexCount;
	this->vertexBuffer = (float*)malloc(vertexCount*6);

	this->bufferID = shapeController.bufferID;

	this->EBOsize = shapeController.EBOsize;
	this->EBObuffer = (uint*)malloc(EBOsize);

	this->cameraDataBuffer[0] = 0.f;
	this->cameraDataBuffer[1] = 0.f;
	this->cameraDataBuffer[2] = 0.1f / 16.f * 9.f;
	this->cameraDataBuffer[3] = 0.1f;

	this->VBO = shapeController.VBO;
	this->VAO = shapeController.VAO;
	this->EBO = shapeController.EBO;
	this->CDB = shapeController.CDB;

	this->shader = shapeController.shader;
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
		glDeleteShader(shader);
	}
}

