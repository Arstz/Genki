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
"	vec2 scale;"
"};"
"out vec4 vertexColor;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(pos*scale, 0.f, 1.f);\n"
"   vertexColor = color;\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec4 vertexColor;\n"
"layout(std140) uniform Borders\n"
"{"
"	vec2 min;\n"
"	vec2 max;\n"
"};"
"void main()\n"
"{\n"
"	vec4 temp = vertexColor;\n"
"if(gl_FragCoord.y > 1080 - min.y) temp = vec4(0.f,0.f,0.f,0.f);\n"
"if(gl_FragCoord.y < 1080 - max.y) temp = vec4(0.f,0.f,0.f,0.f);\n"
"if(gl_FragCoord.x < min.x) temp = vec4(0.f,0.f,0.f,0.f);\n"
"if(gl_FragCoord.x > max.x) temp = vec4(0.f,0.f,0.f,0.f);\n"
"FragColor = temp;\n"
"}\0";

GLFWwindow* ShapeController::window = nullptr;
int ShapeController::shader = 0;

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

void ShapeController::initBuffers() {
	glGenBuffers(1, &CDB);
	glBindBuffer(GL_UNIFORM_BUFFER, CDB);

	glUniformBlockBinding(
		shader,
		glGetUniformBlockIndex(shader, "Camera"),
		1
	);
	
	
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	glGenBuffers(1, &bordersBuffer);
	glBindBuffer(GL_UNIFORM_BUFFER, bordersBuffer);

	glUniformBlockBinding(
		shader,
		glGetUniformBlockIndex(shader, "Borders"),
		2
	);

	glBufferData(
		GL_UNIFORM_BUFFER,
		sizeof(float) * 4,
		borders,
		GL_STATIC_DRAW
	);

	

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
	glUseProgram(shader);
//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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


	glBindBufferBase(GL_UNIFORM_BUFFER, 1, CDB);//suka

	glBindBufferBase(GL_UNIFORM_BUFFER, 2, bordersBuffer);//suka

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindVertexArray(VAO);

	glEnableVertexAttribArray(VERTEX_ATTRIB_ARRAY_1);
	glEnableVertexAttribArray(VERTEX_ATTRIB_ARRAY_2);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);


	glBufferData(
		GL_ARRAY_BUFFER,
		sizeof(float) * vertexCount * VERTEX_SIZE,
		vertexBuffer,
		GL_STREAM_DRAW
	);
	glBindBuffer(GL_UNIFORM_BUFFER, CDB);
	glBufferData(
		GL_UNIFORM_BUFFER,
		sizeof(float) * CAMERA_DATA_SIZE,
		cameraDataBuffer,
		GL_STATIC_DRAW
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

ShapeController::ShapeController() {
	this->shapeGroup = ShapeGroup(0, nullptr, 1.f, 0.f, 0.f, 0);

	this->vertexCount = 0;
	this->vertexBuffer = (float*)malloc(0);

	this->EBOsize = 0;
	this->EBObuffer = (uint*)malloc(0);

	this->cameraDataBuffer[0] = 0.1f / 16.f * 9.f;
	this->cameraDataBuffer[1] = 0.1f;

	this->borders[0] = 960 -300;
	this->borders[1] = 540 -300;
	this->borders[2] = 960 + 300;
	this->borders[3] = 540 + 300;

	this->VBO = 0;
	this->VAO = 0;
	this->EBO = 0;
	this->CDB = 0;
	this->bordersBuffer = 0;
		
	if (window) {
		initBuffers();
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
		glDeleteBuffers(1, &bordersBuffer);
	}
}

