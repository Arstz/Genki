#include <vector>
#include <iostream>
#include "Engine.h"

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

	return 0;
}
