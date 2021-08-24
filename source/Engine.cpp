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

//engine data

GLFWwindow* Engine::window = nullptr;
int Engine::height = 1000;
int Engine::width = 1500;

EngineFunction Engine::currentFunction = Engine::init;

std::vector<ShapeController*> Engine::shapeControllers;
std::vector<Shader*> Engine::shaders;

void Engine::init() {
	Window::init(width, height);
	window = Window::getWindow();
	GUIcanvas::setWindow();

	ShapeController::setWindow(window);
	initShaders();

	Engine::initMainMenu();
}

constexpr int TRIANGLE_DRAW_INDEX = 0;
constexpr int TRIANGLE_DRAW_BORDERS_INDEX = 1;
constexpr int TRIANGLE_DRAW_CAMERA_INDEX = 2;

void Engine::initShaders() {
	shaders = std::vector<Shader*>(3, nullptr);

	//triangleDraw

	std::string TriangleDrawVertexShaderSource = ShaderSource(TriangleDraw_glslv).getSource(std::vector<std::string>{"SCALE_X"}, std::vector<std::string>{std::to_string(SCREEN_RATIO)});

	const char* triangleDrawSources[] {
		&TriangleDrawVertexShaderSource[0],
		&TriangleDraw_glslf[0]
	};

	int triangleDrawShaderTypes[] {GL_VERTEX_SHADER, GL_FRAGMENT_SHADER};

	std::vector<BufferProperties> triangleDrawProperties {};

	shaders[TRIANGLE_DRAW_INDEX] = new Shader(triangleDrawShaderTypes, (char* const*)triangleDrawSources, 2, triangleDrawProperties);

	//triangleDrawBorders

	std::string TriangleDrawBordersVertexShaderSource = ShaderSource(TriangleDrawBorders_glslv).getSource(std::vector<std::string>{"SCALE_X"}, std::vector<std::string>{std::to_string(SCREEN_RATIO)});

	const char* triangleDrawBordersSources[] {
		&TriangleDrawBordersVertexShaderSource[0],
		&TriangleDrawBorders_glslf[0]
	};

	int triangleDrawBordersShaderTypes[]{GL_VERTEX_SHADER, GL_FRAGMENT_SHADER};

	std::vector<BufferProperties> triangleDrawBordersProperties{
		BufferProperties(GL_UNIFORM_BUFFER, sizeof(float) * 4, "Borders"),
	};

	shaders[TRIANGLE_DRAW_BORDERS_INDEX] = new Shader(triangleDrawBordersShaderTypes, (char* const*)triangleDrawBordersSources, 2, triangleDrawBordersProperties);

	//triangleDrawCamera

	const char* triangleDrawCameraSources[] {
		&TriangleDrawCamera_glslv[0],
		&TriangleDrawCamera_glslf[0]
	};

	int triangleDrawCameraShaderTypes[]{GL_VERTEX_SHADER, GL_FRAGMENT_SHADER};

	std::vector<BufferProperties> triangleDrawCameraProperties{
		BufferProperties(GL_UNIFORM_BUFFER, sizeof(float) * 4, "Camera"),
	};

	shaders[TRIANGLE_DRAW_CAMERA_INDEX] = new Shader(triangleDrawCameraShaderTypes, (char* const*)triangleDrawCameraSources, 2, triangleDrawCameraProperties);
}

void Engine::pollEvents() {
	glfwPollEvents();
}

void Engine::sex() {
	std::cout << "$3cks" << "\n";
}

//main menu data

constexpr int GAME_START_BUTTON_INDEX = 0;

void Engine::initMainMenu() {
	ShapeController* GUIshapeController = new ShapeController(shaders[TRIANGLE_DRAW_INDEX], nullptr);
	GUIcanvas::init(GUIshapeController);
	GUIshapeController = nullptr;
	GUIcanvas::addActionButton(Vector2f(0.5f, 0.f), Vector2f(0.2f, 0.2f), 4, Color(1.f, 0.f, 0.f, 1.f), Color(0.f, 0.f, 0.f, 1.f));
	GUIcanvas::addActionButton(Vector2f(-0.5f, 0.f), Vector2f(0.2f, 0.2f), 5, Color(1.f, 0.f, 0.f, 1.f), Color(0.f, 0.f, 0.f, 1.f));
	currentFunction = Engine::updateMainMenu;
	updateMainMenu();
}

void Engine::updateMainMenu() {
	pollEvents();
	GUIcanvas::update();
	if (std::find(GUIcanvas::getActivatedButtonIndexes().begin(), GUIcanvas::getActivatedButtonIndexes().end(), 4) != GUIcanvas::getActivatedButtonIndexes().end()) {
		GUIcanvas::clear();
		initGame();
	}

	if (std::find(GUIcanvas::getActivatedButtonIndexes().begin(), GUIcanvas::getActivatedButtonIndexes().end(), 5) != GUIcanvas::getActivatedButtonIndexes().end()) {
		GUIcanvas::reset();
		initTest();
		return;
	}

	Window::clear();
	GUIcanvas::draw();
	glfwSwapBuffers(window);
}

//game data

void Engine::initGame() {
	shapeControllers = std::vector<ShapeController*>(1);
	void* levelShaderData[1];
	float cameraBufferData[]{0, 0, 0.1f * SCREEN_RATIO, 0.1f};
	levelShaderData[0] = (void*)cameraBufferData;

	shapeControllers[0] = new ShapeController(shaders[TRIANGLE_DRAW_CAMERA_INDEX], levelShaderData);

	start = std::chrono::system_clock::now();
	player = Player();
	PlayerBindingEvent::player = &player;

	LevelEvent::setShapeGroupsSize(10);
	LevelEvent::setShapeController(shapeControllers[0]);

	EventController::loadLevel("a");
	currentFunction = Engine::updateGame;
	updateGame();
}

void Engine::updateGame() {
	pollEvents();
	pollKeyEvents();

	auto end = std::chrono::system_clock::now();
	frameTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() - currentTime;
	currentTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

	EventController::update(currentTime);
	AnimationController::update(frameTime);

	Window::clear();
	shapeControllers[0]->draw();

	glfwSwapBuffers(window);
}

//editor data

void Engine::initEditor() {
	currentFunction = Engine::updateEditor;
}

void Engine::updateEditor() {
	pollEvents();
}

//test data

float Engine::frameTime = 0;
float Engine::currentTime = 0;
std::chrono::system_clock::time_point Engine::start = std::chrono::system_clock::now();

Player Engine::player = Player();

std::list<GUIinteractiveObject*>::iterator Engine::zhertva;

constexpr int LEVEL_SHAPECONTROLLER_INDEX = 0;

void Engine::initTest() {
	shapeControllers = std::vector<ShapeController*>(1);

	void* GUIshaderData[1];
	float borderBufferData[]{width / 2.f - 300.f, height - (height / 2.f - 300.f), width / 2.f + 300.f, height - (height / 2.f + 300.f)};
	GUIshaderData[0] = (void*)borderBufferData;

	ShapeController* GUIshapeController = new ShapeController(shaders[TRIANGLE_DRAW_BORDERS_INDEX], GUIshaderData);
	GUIcanvas::init(GUIshapeController);
	GUIshapeController = nullptr;

	void* levelShaderData[1];
	float cameraBufferData[]{10.f, 0, 0.1f * SCREEN_RATIO, 0.1f};
	levelShaderData[0] = (void*)cameraBufferData;

	shapeControllers[LEVEL_SHAPECONTROLLER_INDEX] = new ShapeController(shaders[TRIANGLE_DRAW_CAMERA_INDEX], levelShaderData);

	start = std::chrono::system_clock::now();
	player = Player();
	PlayerBindingEvent::player = &player;

	LevelEvent::setShapeGroupsSize(10);
	LevelEvent::setShapeController(shapeControllers[0]);

	EventController::loadLevel("a");

//	EventController::saveLevel("a", EventController::level);	

	initGUI();
	currentFunction = Engine::updateTest;
}

void Engine::updateTest() {
	pollEvents();
	pollKeyEvents();
	auto end = std::chrono::system_clock::now();
	frameTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() - currentTime;
	currentTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	GUIcanvas::update();
	EventController::update(currentTime);
	AnimationController::update(frameTime);
	if (std::find(GUIcanvas::getActivatedButtonIndexes().begin(), GUIcanvas::getActivatedButtonIndexes().end(), 3) != GUIcanvas::getActivatedButtonIndexes().end()) {
		std::cout << "Ya vas vseh poreshayu!\n";
		GUIcanvas::clear();
	}
	if (std::find(GUIcanvas::getActivatedButtonIndexes().begin(), GUIcanvas::getActivatedButtonIndexes().end(), 4) != GUIcanvas::getActivatedButtonIndexes().end()) {
		std::cout << "Ya spokoinyi chel!\n";
	}
	
	Window::clear();
	shapeControllers[LEVEL_SHAPECONTROLLER_INDEX]->draw();
	GUIcanvas::draw();

	glfwSwapBuffers(window);
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

	GUIcanvas::addActionButton(Vector2f(-0.5f, 0.f), Vector2f(0.2f, 0.2f), 3, Color(1.f, 0.f, 0.f, 1.f), Color(0.f, 1.f, 1.f, 1.f));
	GUIcanvas::addActionButton(Vector2f(0.5f, 0.f), Vector2f(0.2f, 0.2f), 4);

	Text::setScale(Vector2f(0.03f, 0.03f));
	GUIobject sampleText = GUIobject(Text::makeText("228AUE1337", Vector2f(-0.5f, -0.4f)), GUIcanvas::shapeController);
}

#define IS_UP_KEY_PRESSED (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
#define IS_LEFT_KEY_PRESSED (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
#define IS_DOWN_KEY_PRESSED (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
#define IS_RIGHT_KEY_PRESSED (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)

void Engine::pollKeyEvents() {
	if (IS_RIGHT_KEY_PRESSED && IS_LEFT_KEY_PRESSED) {
		if (player.lastDirectionX == 1) {
			player.move(-1.f, 0.f);
		}
		else player.move(1.f, 0.f);
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

//engine data

void Engine::callUpdate() {
	currentFunction();
}

bool Engine::running() {
	return Window::running();
}

void Engine::destroy() {
	AnimationController::destroy();
	shapeControllers[0]->destroy();
	EventController::destroy();
}

void Engine::terminate() {
	glfwTerminate();
}
