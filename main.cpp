#include <vector>
#include <iostream>
#include "Engine.h"

void sex()
{
	std::cout << "$3cks" << "\n";
}

int main()
{
	Engine game;
	while (game.running()) {

		game.update();

		game.render();
	}
	return 0;
}