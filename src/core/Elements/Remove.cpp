#include "Remove.h"

Remove::Remove(Rectangle pos, int* val,int removeVal):Element(pos)
{
	this->val = val;
	if (removeVal > 0)
		this->removeVal = removeVal;
	else
		this->removeVal = 1;
}

bool Remove::press()
{
	if (CheckCollisionPointRec(GetMousePosition(), getPos()))
	{
		if (*val > 0)
		{
			(*val) -= removeVal;
			if (*val <= 0)
				(*val) = 0;
		}

		return true;
	}
	return false;
}

void Remove::draw()
{
	Element::draw();
	Rectangle pos = getPos();
	DrawTriangle({ pos.x + pos.width / 2,pos.y }, { pos.x,pos.y + pos.height / 5.0f * 4.0f },
		{ pos.x + pos.width,pos.y + pos.height / 5.0f * 4.0f }, BLACK);
}