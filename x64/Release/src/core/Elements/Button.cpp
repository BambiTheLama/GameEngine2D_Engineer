#include "Button.h"
#include "../Properties.h"
Button::Button(Rectangle pos,std::string name)
{
	this->pos = pos;
	this->name = name;
}

void Button::update(float deltaTime)
{
	if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && state == ButtonState::holdAtButton)
	{
		if (CheckCollisionPointRec(GetMousePosition(), pos))
			state = ButtonState::pressed;
	}
	else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		if (CheckCollisionPointRec(GetMousePosition(), pos))
			state = ButtonState::holdAtButton;
	}
	else if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && state != ButtonState::non)
	{
		if (CheckCollisionPointRec(GetMousePosition(), pos))
			state = ButtonState::holdAtButton;
		else
			state = ButtonState::holdOutOfButton;
	}
	else
		state = ButtonState::non;

}

bool Button::press()
{
	return CheckCollisionPointRec(GetMousePosition(), pos) && ButtonState::pressed == state;
}

void Button::draw()
{
	Color c = BLUE;
	switch (state)
	{
	case ButtonState::pressed:
		c = YELLOW;
		break;
	case ButtonState::holdAtButton:
		c = YELLOW;
		break;
	case ButtonState::holdOutOfButton:
		c = RED;
		break;
	case ButtonState::non:
		break;
	}
	DrawRectangleRounded(pos, 0.42137, 10, c);
	DrawRectangleRoundedLines(pos, 0.42137, 10, 4, BLACK);
	const char* text = name.c_str();
	Vector2 s = textSize(text, textStandardSize);
	drawText(text, pos.x+(pos.width-s.x)/2, pos.y + (pos.height - s.y) / 2, textStandardSize, BLACK);
}