#include "Engine.h"
#include "EventController.h"
#include "AnimationController.h"
#include "Shape.h"
#include "ShapeGroup.h"
#include "LevelEvent\LevelEvent.h"
#include "Window.h"
#include "ShapeController.h"
#include "GUIcanvas.h"
#include "Vector2f.h"
#include "GUI.h"
#include "Text.h"
#include "Shader.h"
#include <initializer_list>
#include "ShaderSource.h"
#include "Shaders/shaders.h"

#include "crtdbg.h"
#include "..\include\CRTDBG\mydbgnew.h"
#ifdef _DEBUG
#define new MYDEBUG_NEW
#endif

#define AAAA (static_cast <float> (rand()) / static_cast <float> (RAND_MAX))
#define BBBB (2.f*static_cast <float> (rand()) / static_cast <float> (RAND_MAX) - 1)/2
#define SCREEN_RATIO (float)height/(float)width

#define IS_UP_KEY_PRESSED (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
#define IS_LEFT_KEY_PRESSED (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
#define IS_DOWN_KEY_PRESSED (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
#define IS_RIGHT_KEY_PRESSED (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)

float Engine::frameTime = 0;
float Engine::currentTime = 0;

int Engine::height = 1000;
int Engine::width = 1500;

Player Engine::player = Player();

GLFWwindow* Engine::window = nullptr;

ShapeController* Engine::GUIshapeController = nullptr;
ShapeController* Engine::levelShapeController = nullptr;

std::chrono::system_clock::time_point Engine::start = std::chrono::system_clock::now();
std::list<GUIinteractiveObject*>::iterator Engine::zhertva;

void Engine::destroy()
{
	AnimationController::destroy();
	levelShapeController->destroy();
	EventController::destroy();
}

void Engine::terminate() {
	glfwTerminate();
}

void Engine::createShaders() {
	int bufferTypes[]{ GL_VERTEX_SHADER, GL_FRAGMENT_SHADER };

	std::vector<BufferProperties> GUIshaderBufferProperties{
		BufferProperties(GL_UNIFORM_BUFFER, sizeof(float) * 4, "Borders"),
	};
	void* GUIshaderData[1];
	float borderBufferData[]{ width/2 - 3000, height - (height / 2 - 3000), width / 2 + 3000, height - (height/2 + 3000) };
	GUIshaderData[0] = (void*)borderBufferData;
	std::string GUIshaderSource = ShaderSource(GUICanvasShader_glslv).getSource(std::vector<std::string>{"SCALE_X"}, std::vector<std::string>{std::to_string(SCREEN_RATIO)});
	const char* GUIshaderSources[] = { &GUIshaderSource[0], &GUICanvasShader_glslf[0] };
	Shader* GUIshader = new Shader(bufferTypes, (char* const*)GUIshaderSources, 2, GUIshaderBufferProperties);

	GUIshapeController = new ShapeController(GUIshader, GUIshaderData);

	std::vector<BufferProperties> levelShaderBufferProperties{
		BufferProperties(GL_UNIFORM_BUFFER, sizeof(float) * 2, "Camera"),
	};	
	void* levelShaderData[1];	
	float cameraBufferData[]{ 0.1f * SCREEN_RATIO, 0.1f };
	levelShaderData[0] = (void*)cameraBufferData;
	const char* levelShaderSources[] = { &LevelShapeControllerShader_glslv[0], &LevelShapeControllerShader_glslf[0] };
	Shader* levelShader = new Shader(bufferTypes, (char* const*)levelShaderSources, 2, levelShaderBufferProperties);	

	levelShapeController = new ShapeController(levelShader, levelShaderData);
}

void Engine::initGUI() {
	float* x = new float(0);
	float* y = new float(0);
	bool* z = new bool(0);
	*z = false;

	GUIcanvas::addSex(Vector2f(0, 0), Vector2f(0.1f, 0.3f));
	GUIcanvas::addSex(Vector2f(-1, -1), Vector2f(0.5f, 0.5f));

	GUIcanvas::addSlider(Vector2f(-0.7f, -0.3f), Vector2f(0, 1), x, y, Vector2f(200, 200), Vector2f(500, 500));
	GUIcanvas::addSlider(Vector2f(-0.5f, -0.5f), Vector2f(0.8f, 0), x, y, Vector2f(200, 200), Vector2f(500, 500));

	zhertva = GUIcanvas::addCheckBox(Vector2f(0.3f, 0.3f), Vector2f(0.1f, 0.1f), z);

	GUIcanvas::addActionButton(Vector2f(-0.5f, 0.f), Vector2f(0.2f, 0.2f), 3,Color(1.f, 0.f, 0.f, 1.f), Color(0.f, 1.f, 1.f, 1.f));
	GUIcanvas::addActionButton(Vector2f(0.5f, 0.f), Vector2f(0.2f, 0.2f), 4);

	Text::setScale(Vector2f(0.03f, 0.03f));
	GUIobject sampleText = GUIobject(Text::makeText("228AUE1337", Vector2f(-0.5f, -0.4f)), GUIcanvas::shapeController);
}

void Engine::init() {
	Window::init(width, height);
	window = Window::getWindow();
	GUIcanvas::setWindow();		
	
	ShapeController::setWindow(window);

	createShaders();

	GUIcanvas::init(GUIshapeController);		

	start = std::chrono::system_clock::now();
	player = Player();
	PlayerBindingEvent::player = &player;

	AnimationController::setTimePointer(&frameTime);

	EventController::currentTime = &currentTime;

	LevelEvent::setShapeGroupsSize(10);
	LevelEvent::setShapeController(levelShapeController);

	EventController::loadLevel("a");

//	EventController::saveLevel("a", EventController::level);	

	initGUI();
}

void Engine::pollEvents() {
	glfwPollEvents();
}

void Engine::update() {
	pollEvents();
	pollKeyEvents();
	auto end = std::chrono::system_clock::now();
	frameTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() - currentTime;
	currentTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	GUIcanvas::update();
	EventController::update();
	AnimationController::update();
	if (std::find(GUIcanvas::getActivatedButtonIndexes().begin(), GUIcanvas::getActivatedButtonIndexes().end(), 3) != GUIcanvas::getActivatedButtonIndexes().end()) {
		std::cout << "Ya vas vseh poreshayu!\n";
		GUIcanvas::clear();
	}
	if (std::find(GUIcanvas::getActivatedButtonIndexes().begin(), GUIcanvas::getActivatedButtonIndexes().end(), 4) != GUIcanvas::getActivatedButtonIndexes().end()) {
		std::cout << "Ya spokoinyi chel!\n";
	}
}

void Engine::render() {
	Window::clear();
	levelShapeController->draw();
	GUIcanvas::draw();
	
	glfwSwapBuffers(window);
}

bool Engine::running() {
	return Window::running();
}

void Engine::pollKeyEvents() {
	if (IS_RIGHT_KEY_PRESSED && IS_LEFT_KEY_PRESSED) {
		if (player.lastDirectionX == 1) {
			player.move(-1.f, 0.f);
		} else player.move(1.f, 0.f);
	}
	else if (IS_LEFT_KEY_PRESSED) {
		player.move(-1.f, 0.f);
		player.lastDirectionX = -1;
	}
	else if (IS_RIGHT_KEY_PRESSED) {
		player.move(1.f, 0.f);
		player.lastDirectionX = 1;
	}
	if (IS_DOWN_KEY_PRESSED && IS_UP_KEY_PRESSED) {
		if (player.lastDirectionY == 1) {
			player.move(0.f, -1.f);
		}
		else player.move(0.f, 1.f);
	}
	else if (IS_DOWN_KEY_PRESSED) {
		player.move(0.f, -1.f);
		player.lastDirectionY = -1;
	}
	else if (IS_UP_KEY_PRESSED) {
		player.move(0.f, 1.f);
		player.lastDirectionY = 1;
	}
}
