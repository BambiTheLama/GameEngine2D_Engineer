#include "Button.h"
#include "../Properties.h"
Button::Button(Rectangle pos,std::string name)
{
	this->pos = pos;
	this->name = name;
}

bool Button::press()
{
	return CheckCollisionPointRec(GetMousePosition(), pos);
}

void Button::draw()
{
	DrawRectangleRounded(pos, 0.42137, 10, BLUE);
	DrawRectangleRoundedLines(pos, 0.42137, 10, 2, BLACK);
	const char* text = name.c_str();
	Vector2 s = textSize(text, textStandardSize);
	drawText(text, pos.x+(pos.width-s.x)/2, pos.y + (pos.height - s.y) / 2, textStandardSize, BLACK);
}