#include "FloatEnter.h"

FloatEnter::FloatEnter(Rectangle pos, std::string name, float* val):Element(pos)
{
	this->name = name;
	this->val = val;
	floatVal = std::to_string(*val);
}
void FloatEnter::update()
{
	if (!pressed)
		return;
	if (!isAnyKeyPressed())
		return;
	int key = keyPressed();
	if (key >= '0' && key <= '9')
	{
		if (floatVal.size() == 1 && floatVal.at(0)=='0')
		{
			floatVal = key;
		}
		else
		{
			floatVal += key;
		}

	}

	if (IsKeyPressed(KEY_BACKSPACE))
	{
		floatVal.pop_back();
		if (floatVal.size() <= 0)
			floatVal = '0';
	}

	if (key == '.' || key == ',')
	{
		for (int i = 0; i < floatVal.size(); i++)
			if (floatVal.at(i) == '.')
				return;
		floatVal += '.';
	}
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
}

void FloatEnter::draw()
{
	Element::draw();
	Rectangle pos = getPos();
	std::string name = this->name +":" + floatVal;
	drawText(name.c_str(), pos.x+2, pos.y+2, textStandardSize, BLACK);

	DrawRectangleLinesEx(pos, 2, pressed ? RED : BLACK);
}