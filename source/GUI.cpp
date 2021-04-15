#include "GUI.h"

bool GUIinteractiveObject::checkCollision(float x, float y){
	return x < RightBorderX && x > LeftBorderX && y < UpBorderY && y > BottomBorderY;
}
