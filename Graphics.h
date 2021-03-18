#pragma once
#define GLEW_STATIC
#define VERTEX_SIZE 6ul
#define CAMERA_DATA_SIZE 4u

#include <list>
#include "Shape.h"
#include <GL/glew.h>
#include <GLFW\glfw3.h>

typedef unsigned int uint;
typedef std::list<Shape*> ShapeList;

class Graphics {
	static ShapeList shapes;

	static uint vertexCount;
	static float* vertexDataBuffer;

	static uint EBOsize;
	static uint* EBObuffer;
	static float* cameraDataBuffer;
	
	static GLuint VBO;
	static GLuint VAO;
	static GLuint EBO;
	static GLuint CDB;

	static GLFWwindow* window;
	static int shader;

	static void updateBuffers();
	static void reallocateBuffers();

	static void initWindow();
	static void compileShader();
	static void initBuffers();
public:
	static float* getCameraValuePointer(uint valueNum);
	static void init();
	static void draw();
	static ShapeList::iterator addShape(Shape* shape);
	static void removeShape(ShapeList::iterator &shapeIterator);
	static bool running();
};