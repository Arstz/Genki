#include <vector>
#include <iostream>
#include "Engine.h"
#define GRAPHICS_INCLUDE

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

	return 0;
}
