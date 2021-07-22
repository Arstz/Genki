#include "Window.h"
#include <iostream>

#include "crtdbg.h"
#include "..\include\CRTDBG\mydbgnew.h"
#ifdef _DEBUG
#define new MYDEBUG_NEW
#endif

float Window::backgroundColor[4] = { 1.f, 1.f, 1.f, 1.f };
GLFWwindow* Window::window = nullptr;
int Window::width = 0;
int Window::height = 0;

void Window::init(int width, int height) {
	Window::width = width;
	Window::height = height;
	glfwInit();
	glfwWindowHint(GLFW_SAMPLES, 4);
	glEnable(GL_MULTISAMPLE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	window = glfwCreateWindow(width, height, "Genki.psd", nullptr, nullptr);
	if (window == nullptr) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cout << "Failed to initialize GLEW" << std::endl;
	}
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

int Window::getWidth() {
	return width;
}

int Window::getHeight() {
	return height;
}
