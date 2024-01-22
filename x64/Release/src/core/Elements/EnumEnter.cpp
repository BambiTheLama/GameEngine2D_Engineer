#include "EnumEnter.h"
EnumEnter::EnumEnter(Rectangle pos, std::string name, int* val, int size, std::string description)
	:IntEnter(pos, name, val)
{
	this->description = description;
	this->size = size;
}

void EnumEnter::update()
{
	if (!pressed)
		return;
	isAnyKeyPressed();

	int key = keyPressed();
	if (key >= '0' && key <= '9')
	{
		(*val) = (*val) * 10 + key - '0';
		if (*val >= size)
			*val = size - 1;
	}

	if (IsKeyPressed(KEY_BACKSPACE))
		(*val) = (*val) / 10;
	if (IsKeyPressed(KEY_UP))
	{
		(*val)++;
		if (*val >= size)
			*val = 0;
	}
	if (IsKeyPressed(KEY_DOWN))
	{
		(*val)--;
		if (*val < 0)
			*val = size - 1;
	}

}

bool EnumEnter::press()
{
	return IntEnter::press();
}

void EnumEnter::draw()
{
	IntEnter::draw();
	Rectangle pos = Element::getPos();
	Vector2 mouse = GetMousePosition();
	if (!CheckCollisionPointRec(mouse, pos))
		return;
	const char* text = description.c_str();
	Vector2 size = textSize(text, textStandardSize);
	Rectangle textPos = { mouse.x - 2,mouse.y - 2,size.x + 4,size.y + 4 };
	DrawRectangleRec(textPos, WHITE);
	DrawRectangleLinesEx(textPos, 2, BLACK);
	drawText(text, mouse.x, mouse.y, textStandardSize, BLACK);
}