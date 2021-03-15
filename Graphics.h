#pragma once
#define GLEW_STATIC
#define VERTEX_SIZE 6ul
#include <list>
#include "Shape.h"
#include <GL/glew.h>
#include <GLFW\glfw3.h>

typedef unsigned int uint;

class Graphics {
	static std::list<Shape>* shapes;

	static uint vertexCount;
	static float* vertexDataBuffer;

	static uint EBOsize;
	static uint* EBObuffer;
	
	static GLuint VBO;
	static GLuint VAO;
	static GLuint EBO;

	static GLFWwindow* window;
	static int shader;

	static void updateBuffers();
	static void reallocateBuffers();

	static void initWindow();
	static void compileShader();
	static void initBuffers();
public:
	static void init();
	static void draw();
	static std::list<Shape>::iterator addShape(Shape shape);
	static void removeShape(std::list<Shape>::iterator &shapeIterator);
	static bool running();
};