#include <vector>
#include <iostream>
#include "Engine.h"

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
	Engine::destroy();
	_CrtMemDumpAllObjectsSince(NULL);
	return 0;
}
