#include "Add.h"
Add::Add(Rectangle pos, int* val) :Element(pos)
{
	this->val = val;
}

bool Add::press()
{
	if (CheckCollisionPointRec(GetMousePosition(), getPos()))
	{
		(*val)++;
		return true;
	}
	return false;
}

void Add::draw()
{
	Element::draw();
	Rectangle pos = getPos();
	DrawCircle(pos.x + pos.width / 2, pos.y + pos.height / 2, pos.width / 2, GRAY);
	DrawRectangle(pos.x + pos.width / 2 - 2, pos.y, 4, pos.height, BLACK);
	DrawRectangle(pos.x, pos.y + pos.height / 2 - 2, pos.width, 4, BLACK);
}