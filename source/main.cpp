#include <vector>
#include <iostream>
#include "Engine.h"
#include "ByteArray.h"

#include "crtdbg.h"
#include "..\include\CRTDBG\mydbgnew.h"
#ifdef _DEBUG
#define new MYDEBUG_NEW
#endif



int main() {
	do {
		Engine::callUpdate();
	} while (Engine::running());

	Engine::terminate();

//	Engine::destroy();
//	_CrtMemDumpAllObjectsSince(NULL);
	return 0;
}
