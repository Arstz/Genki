#include <vector>
#include <iostream>
#include "Engine.h"
#include "ByteArray.h"

#include "crtdbg.h"
#include "..\include\CRTDBG\mydbgnew.h"
#ifdef _DEBUG
#define new MYDEBUG_NEW
#endif

void sex()
{
	std::cout << "$3cks" << "\n";
}



int main()
{
//	Engine engine = Engine();

	Engine::init();
	while (Engine::running()) {

		Engine::update();
		Engine::render();
	}

	Engine::terminate();
//	Engine::destroy();
//	_CrtMemDumpAllObjectsSince(NULL);
	return 0;
}
