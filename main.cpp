#include <vector>
#include <iostream>
#include "Engine.h"
#define GRAPHICS_INCLUDE

#include "crtdbg.h"
#include "mydbgnew.h"
#ifdef _DEBUG
#define new MYDEBUG_NEW
#endif

void sex()
{
	std::cout << "$3cks" << "\n";
}

int main()
{
	Engine::init();
	while (Engine::running()) {
		Engine::update();
		Engine::render();
	}

	Engine::terminate();
	_CrtMemDumpAllObjectsSince(NULL);
	return 0;
}
