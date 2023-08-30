#include "FloatEnter.h"
std::string floatToString(float f)
{
	std::string s;
	int tmp = f;
	if (tmp == 0)
		s = "0";
	else if (tmp < 0)
		s = "-";
	std::string s2;
	while (tmp != 0)
	{
		s2 += (tmp % 10) + '0';
		tmp /= 10;
	}
	for (int i = s2.size() - 1; i >= 0; i--)
		s += s2.at(i);

	f -= (int)f;
	if (f != 0)
	{
		s += ".";
		for (int i = 0; i < 6; i++)
			s += ((int)(pow(10, i + 1) * f) % 10) + '0';
		while (s.at(s.size() - 1) == '0')
		{
			s.pop_back();
		}
	}
	return s;
}

std::string stringValue(std::string s, int c)
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
	else if (c == '-')
	{
		if (s.at(0) != '-')
			s = '-' + s;
		else
			s = s.substr(1);
	}
	if (IsKeyPressed(KEY_BACKSPACE))
	{
		s.pop_back();
		if (s.size() <= 0)
			s = "0";
		else if (s.size() == 1 && s.at(0) == '-')
			s = "0";

	}
	return s;
}

FloatEnter::FloatEnter(Rectangle pos, std::string name, float* val):Element(pos)
{
	this->name = name;
	this->val = val;
	if(val)
		floatVal = floatToString(*val);
}
void FloatEnter::update()
{
	if (!pressed)
		return;
	if (!isAnyKeyPressed())
		return;
	int key = keyPressed();
	floatVal = stringValue(floatVal, key);
	(*val) = std::stof(floatVal);
}

bool FloatEnter::press()
{
	if (CheckCollisionPointRec(GetMousePosition(), getPos()))
	{
		pressed = true;
		return true;
	}
	return false;
}

void FloatEnter::unPress()
{
	pressed = false;
	floatVal = floatToString(*val);
}

void FloatEnter::draw()
{
	Element::draw();
	Rectangle pos = getPos();
	std::string name = this->name +":" + floatVal;
	drawText(name.c_str(), pos.x+2, pos.y+2, textStandardSize, BLACK);

	DrawRectangleLinesEx(pos, 2, pressed ? RED : BLACK);
}