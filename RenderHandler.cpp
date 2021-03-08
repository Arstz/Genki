#include "RenderHandler.h"

void RenderHandler::render()
{
	for (int i = 0; i < shapeCount; i++) {
		mainWindow->draw(shapes[i]);
	}
}
