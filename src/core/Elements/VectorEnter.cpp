#include "VectorEnter.h"
#include "FloatEnter.h"
VectorEnter::VectorEnter(Rectangle pos, std::string name, Vector2* val) :Element(pos)
{
	this->val = val;
	this->name = name;
	if (val)
	{
		floatVal = floatToString(val->x);
		floatVal2 = floatToString(val->y);
	}

}
void VectorEnter::updateVal(Vector2* val) 
{ 
	this->val = val; 
	if (val)
	{
		floatVal = floatToString(val->x);
		floatVal2 = floatToString(val->y);
		val->x = std::stof(floatVal);
		val->y = std::stof(floatVal2);
	}
}



void VectorEnter::update()
{
	if (pressed)
	{
		if (!isAnyKeyPressed())
			return;
		int v = 0;
		int key = keyPressed();
		
		if (left)
		{
			floatVal = stringValue(floatVal, key);
			val->x = std::stof(floatVal);

		}
		else
		{
			floatVal2 = stringValue(floatVal2, key);
			val->y = std::stof(floatVal2);
		}
	}
	else
	{
		floatVal = floatToString(val->x);
		floatVal2 = floatToString(val->y);
	}
}

void VectorEnter::updatePos()
{
	Rectangle pos = getPos();
	pos1 = pos;
	pos1.width /= 2;
	pos2 = pos;
	pos2.width /= 2;
	pos2.x += pos2.width;
}

bool VectorEnter::press()
{
	pressed = CheckCollisionPointRec(GetMousePosition(), getPos());
	if (pressed)
		left = CheckCollisionPointRec(GetMousePosition(), pos1);
	
	return pressed;
}

void VectorEnter::unPress()
{
	pressed = false;
}

void VectorEnter::draw()
{
	Element::draw();
	DrawRectangleLinesEx(pos1, 2, pressed && left ? RED : BLACK);
	DrawRectangleLinesEx(pos2, 2, pressed && !left ? RED : BLACK);
	drawText(floatVal.c_str(), pos1.x + 2, pos1.y + 2, textStandardSize, BLACK);
	drawText(floatVal2.c_str(), pos2.x + 2, pos2.y + 2, textStandardSize, BLACK);
}