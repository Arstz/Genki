#include "ShapeController.h"
#include <iostream>

GLuint bufferID = 0;

std::list<ShapeGroup*> ShapeController::shapeGroups;

uint ShapeController::vertexCount = 0;
float* ShapeController::vertexBuffer = new float[0];

GLuint ShapeController::bufferID = 0;

uint ShapeController::EBOsize = 0;
uint* ShapeController::EBObuffer = new uint[0];
float ShapeController::cameraDataBuffer[4] = {0.f, 0.f, 0.1f / 16.f * 9.f, 0.1f};

GLuint ShapeController::VBO = 0;
GLuint ShapeController::VAO = 0;
GLuint ShapeController::EBO = 0;
GLuint ShapeController::CDB = 0;

int ShapeController::shader = 0;

GLFWwindow* ShapeController::window = nullptr;

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

void ShapeController::updateBuffers() {
	uint positionOffsetCounter = 0;
	uint colorOffsetCounter = vertexCount * 2;

	for (ShapeGroup* shapeGroup : shapeGroups) {
		writeToVertexbuffer(shapeGroup, positionOffsetCounter, colorOffsetCounter, 0, 0);
	}
}

void ShapeController::writeToVertexbuffer(
	ShapeGroup* shapeGroup,
	uint& positionOffsetCounter,
	uint& colorOffsetCounter,
	float positionX,
	float positionY
) {
	positionX += shapeGroup->positionX;
	positionY += shapeGroup->positionY;
	for (int i = 0; i < shapeGroup->shapeCount; i++) {
		for (int j = 0; j < shapeGroup->shapes[i].vertexCount * 2; j += 2) {
			vertexBuffer[positionOffsetCounter + j] = shapeGroup->shapes[i].vertexCoords[j] + positionX;
			vertexBuffer[positionOffsetCounter + j + 1] = shapeGroup->shapes[i].vertexCoords[j + 1] + positionY;
		}
		positionOffsetCounter += shapeGroup->shapes[i].vertexCount * 2;

		for (int j = 0; j < shapeGroup->shapes[i].vertexCount * 4; j++) {
			vertexBuffer[colorOffsetCounter + j] = shapeGroup->shapes[i].vertexColors[j];
		}
		colorOffsetCounter += shapeGroup->shapes[i].vertexCount * 4;
	}
	for (int i = 0; i < shapeGroup->shapeGroupCount; i++) {
		writeToVertexbuffer(&shapeGroup->shapeGroups[i], positionOffsetCounter, colorOffsetCounter, positionX, positionY);
	}
}

void ShapeController::writeToEBObuffer(ShapeGroup* shapeGroup, uint &EBOoffsetCounter) {
	for (int i = 0; i < shapeGroup->shapeCount; i++) {
		for (int j = 0; j < shapeGroup->shapes[i].EBOsize; j++) {
			EBObuffer[EBOoffsetCounter + j] = shapeGroup->shapes[i].vertexIDs[j] + EBOoffsetCounter;
		}
		EBOoffsetCounter += shapeGroup->shapes[i].EBOsize;
	}
	for (int i = 0; i < shapeGroup->shapeGroupCount; i++) {
		writeToEBObuffer(&shapeGroup->shapeGroups[i], EBOoffsetCounter);
	}
}


void ShapeController::reallocateBuffers() {
	delete[] vertexBuffer;
	vertexBuffer = new float[vertexCount * VERTEX_SIZE];

	delete[] EBObuffer;
	EBObuffer = new uint[EBOsize];

	glVertexAttribPointer(
		1,
		4,
		GL_FLOAT,
		GL_FALSE,
		4 * sizeof(GLfloat),
		(GLvoid*)(2 * vertexCount * sizeof(float)));

	uint EBOoffsetCounter = 0;
	for (ShapeGroup* group : shapeGroups) {
		for (ShapeGroup* shapeGroup : shapeGroups) {
			writeToEBObuffer(shapeGroup, EBOoffsetCounter);
		}
	}

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * EBOsize, EBObuffer, GL_STATIC_DRAW);
}

void ShapeController::setWindow(GLFWwindow* window) {
	ShapeController::window = window;
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

void ShapeController::init() {
	setWindow(Window::getWindow());
	initShader();
	initBuffers();
	
//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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

	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(shader);
	glDrawElements(GL_TRIANGLES, EBOsize, GL_UNSIGNED_INT, 0);
	glfwSwapBuffers(window);
}

std::list<ShapeGroup*>::iterator ShapeController::addShape(Shape* shape) {
	shapeGroups.push_front(new ShapeGroup(shape));
	vertexCount += shape->vertexCount;
	EBOsize += shape->EBOsize;
	reallocateBuffers();
	return shapeGroups.begin();
}

std::list<ShapeGroup*>::iterator ShapeController::addShapeGroup(ShapeGroup* shapeGroup) {
	shapeGroups.push_front(shapeGroup);
	vertexCount += shapeGroup->getVertexCount();
	EBOsize += shapeGroup->getEBOsize();
	reallocateBuffers();
	return shapeGroups.begin();
}

void ShapeController::removeShapeGroup(std::list<ShapeGroup*>::iterator& shapeGroupIterator) {
	vertexCount -= (*shapeGroupIterator)->getVertexCount();
	EBOsize -= (*shapeGroupIterator)->getEBOsize();
//	(*shapeIterator)->~Shape(); kracivo EEEE
	delete *shapeGroupIterator;
	shapeGroups.erase(shapeGroupIterator);
	reallocateBuffers();
}