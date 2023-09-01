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

	DrawTriangle({ pos.x + pos.width / 2,pos.y + pos.height }, { pos.x + pos.width,pos.y + pos.height / 5.0f },
		{ pos.x,pos.y + pos.height / 5.0f }, BLACK);
}