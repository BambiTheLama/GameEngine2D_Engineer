#include "IntEnter.h"

IntEnter::IntEnter(Rectangle pos, std::string name, int* val):Element(pos)
{
	this->name = name;
	this->val = val;
}

void IntEnter::update()
{
	if (!pressed)
		return;
	isAnyKeyPressed();

	int key = keyPressed();
	if (key >= '0' && key <= '9')
		(*val) = (*val) * 10 + key-'0';
	else if (key == '-')
		(*val) = -(*val);

	if (IsKeyPressed(KEY_BACKSPACE))
		(*val) = (*val) / 10;

}

bool IntEnter::press()
{
	pressed = CheckCollisionPointRec(GetMousePosition(), getPos());
	return pressed;
}

void IntEnter::unPress()
{
	pressed = false;
}

void IntEnter::draw()
{
	Element::draw();
	Rectangle pos = getPos();
	if (pressed)
		DrawRectangleLinesEx(pos, 2, RED);
	drawText((name + std::to_string(*val)).c_str(), pos.x, pos.y, textStandardSize, BLACK);
}