#pragma once
#include "raylib.h"
#include <string>
enum class ButtonState
{
	non, holdAtButton, holdOutOfButton,pressed
};
class Button
{
	Rectangle pos;
	std::string name;
	ButtonState state = ButtonState::non;
public:
	Button(Rectangle pos,std::string name="");

	void update(float deltaTime);

	bool press();

	void draw();
};

