#pragma once
#include "Graphics.h"
#include <iostream>

ShapeList Graphics::shapes;

uint Graphics::vertexCount = 0;
float* Graphics::vertexDataBuffer = new float[0];

uint Graphics::EBOsize = 0;
uint* Graphics::EBObuffer = new uint[0];
float* Graphics::cameraDataBuffer = new float[] {0.f, 0.f, 0.1f/16.f*9.f, 0.1f};
float* Graphics::backgroundColor = new float[] {1.f, 1.f, 1.f, 1.f};

GLuint Graphics::VBO = 0;
GLuint Graphics::VAO = 0;
GLuint Graphics::EBO = 0;
GLuint Graphics::CDB = 0;

int Graphics::shader = 0;

GLFWwindow* Graphics::window = nullptr;

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
"   gl_Position = vec4((pos.x-offset.x)*scale.x, (pos.y-offset.y)*scale.y, 0.f, 1.0f);\n"
"   vertexColor = color;\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec4 vertexColor;\n"
"void main()\n"
"{\n"
"   FragColor = vertexColor;\n"
"}\n\0";

void Graphics::initBuffers() {
	glGenBuffers(1, &CDB);
	glBindBuffer(GL_UNIFORM_BUFFER, CDB);

	glUniformBlockBinding(
		shader, 
		glGetUniformBlockIndex(shader, "Camera"), 
		1
	);
	glBindBufferBase(GL_UNIFORM_BUFFER, 1, CDB);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glVertexAttribPointer(
		0, 
		2, 
		GL_FLOAT, 
		GL_FALSE, 
		2 * sizeof(GLfloat), 
		(GLvoid*)0);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
}

void Graphics::updateBuffers() {
	uint colorOffsetCounter = vertexCount * 2;
	uint positionOffsetCounter = 0;

	for (Shape* shape : shapes) {
		for (int i = 0; i < shape->vertexCount * 2; i++)
			vertexDataBuffer[positionOffsetCounter + i] = shape->vertexCoords[i];
		positionOffsetCounter += shape->vertexCount * 2;

		for (int i = 0; i < shape->vertexCount * 4; i++)
			vertexDataBuffer[colorOffsetCounter + i] = shape->vertexColors[i];
		colorOffsetCounter += shape->vertexCount * 4;
	}
}

void Graphics::reallocateBuffers() {
	delete[] vertexDataBuffer;
	vertexDataBuffer = new float[vertexCount * VERTEX_SIZE];

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
	for (Shape* shape : shapes) {
		for (int i = 0; i < shape->EBOsize; i++)
			EBObuffer[EBOoffsetCounter + i] = shape->vertexIDs[i] + EBOoffsetCounter;
		EBOoffsetCounter += shape->EBOsize;
	}

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * EBOsize, EBObuffer, GL_STATIC_DRAW);
	glClearColor(backgroundColor[0], backgroundColor[1], backgroundColor[2], backgroundColor[3]);
}

void Graphics::initWindow() {
	window = glfwCreateWindow(1920, 1080, "Genki.psd", nullptr, nullptr);
	if (window == nullptr) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cout << "Failed to initialize GLEW" << std::endl;
	}
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
}

void Graphics::compileShader() {
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

void Graphics::init() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	initWindow();
	compileShader();
	initBuffers();
	
//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

void Graphics::draw() {
	updateBuffers();

	glBufferData(
		GL_ARRAY_BUFFER, 
		sizeof(float) * vertexCount * VERTEX_SIZE,
		vertexDataBuffer,
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

ShapeList::iterator Graphics::addShape(Shape* shape) {
	shapes.push_front(shape);
	vertexCount += shape->vertexCount;
	EBOsize += shape->EBOsize;
	reallocateBuffers();
	return shapes.begin();
}

void Graphics::removeShape(ShapeList::iterator &shapeIterator) {
	vertexCount += (*shapeIterator)->vertexCount;
	EBOsize += (*shapeIterator)->EBOsize;
	shapes.erase(shapeIterator);
	reallocateBuffers();
}

bool Graphics::running() {
	return !glfwWindowShouldClose(window);
}
float* Graphics::getBackgroundColorValuePointer(uint valueNum) {
	return &cameraDataBuffer[valueNum];
}

float* Graphics::getCameraValuePointer(uint valueNum) {
	return &backgroundColor[valueNum];
}

GLFWwindow* Graphics::getWindow() {
	return window;
}

//	.E:[&]->* sam ahuel