#include "Window.h"
#include <iostream>

#include "crtdbg.h"
#include "..\include\CRTDBG\mydbgnew.h"
#ifdef _DEBUG
#define new MYDEBUG_NEW
#endif

float Window::backgroundColor[4] = { 1.f, 1.f, 1.f, 1.f };
GLuint Window::currentBufferID = 1;
GLuint Window::currentAttribArrayID = 0;
GLFWwindow* Window::window = nullptr;

void Window::init() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

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

GLFWwindow* Window::getWindow() {
	return window;
}

float* Window::getBackgroundColorValuePointer(uint valueNum) {
	return &backgroundColor[valueNum];
}

bool Window::running() {
	return !glfwWindowShouldClose(window);
}

void Window::clear() {
	
	glClearColor(backgroundColor[0], backgroundColor[1], backgroundColor[2], backgroundColor[3]);
	glClear(GL_COLOR_BUFFER_BIT);
}

GLuint Window::generateBufferID() {
	return currentBufferID++;
}

GLuint Window::generateAttribArray() {
	return currentAttribArrayID++;
}
