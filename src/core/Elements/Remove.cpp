#include "Remove.h"

Remove::Remove(Rectangle pos, int* val):Element(pos)
{
	this->val = val;
}

bool Remove::press()
{
	if (CheckCollisionPointRec(GetMousePosition(), getPos()))
	{
		if(*val>0)
			(*val)--;
		return true;
	}
	return false;
}

void Remove::draw()
{
	Element::draw();
	Rectangle pos = getPos();
	DrawCircle(pos.x + pos.width / 2, pos.y + pos.height / 2, pos.width / 2, GRAY);
	DrawRectangle(pos.x, pos.y + pos.height / 2 - 2, pos.width, 4, BLACK);
}