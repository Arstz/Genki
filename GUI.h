#pragma once

class GUIobject
{
protected:
	float positionX;
	float positionY;
};

class GUIinteractiveObject : public GUIobject
{
public:	
	virtual bool interact(bool mouseState, float x, float y) = 0;
protected:
	float LeftBorderX;
	float RightBorderX;
	float UpBorderY;
	float BottomBorderY;
	bool checkCollision(float x, float y);
};

class CheckBox : public GUIinteractiveObject
{
public:
	bool* state;
};

