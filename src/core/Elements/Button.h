#pragma once
#include "raylib.h"
#include <string>
class Button
{
	Rectangle pos;
	std::string name;
public:
	Button(Rectangle pos,std::string name="");

	bool press();

	void draw();
};

