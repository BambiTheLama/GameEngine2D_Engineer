#include "VectorEnter.h"

VectorEnter::VectorEnter(Rectangle pos, std::string name, Vector2* val) :Element(pos)
{
	this->val = val;
	this->name = name;
}
void VectorEnter::updateVal(Vector2* val) 
{ 
	this->val = val; 
	if (val != NULL)
	{
		printf("PUNKT:%lf %lf\n", val->x, val->y);
		if(val->x==(int)val->x)
			floatVal = std::to_string((int)val->x);
		else
			floatVal = std::to_string(val->x);

		if (val->y == (int)val->y)
			floatVal2 = std::to_string((int)val->y);
		else
			floatVal2 = std::to_string(val->y);
		val->x = std::stof(floatVal);
		val->y = std::stof(floatVal2);
	}
}

std::string VectorEnter::stringValue(std::string s, int c)
{
	if (c >= '0' && c <= '9')
	{
		if (s.size() <= 1 && s.at(0) == '0')
			s = c;
		else
			s += c;
	}
	else if (c == '.' || c == ',')
	{
		int n = s.size();
		for (int i = 0; i < n; i++)
			if (s.at(i) == '.')
				return s;
		s += '.';
	}
	if (IsKeyPressed(KEY_BACKSPACE))
	{
		s.pop_back();
		if (s.size() <= 0)
			s = "0";
	}
	return s;
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