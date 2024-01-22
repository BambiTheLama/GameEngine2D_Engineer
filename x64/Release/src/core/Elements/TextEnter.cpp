#include "TextEnter.h"
#include "../Properties.h"
TextEnter::TextEnter(Rectangle pos,std::string name, std::string *text) :Element(pos)
{
	this->text = text;
	this->name = name;
}

void TextEnter::update()
{
	if (pressed && isAnyKeyPressed())
	{
		int key = keyPressed();
		if (key >= 'A' && key <= 'Z')
		{
			if (IsKeyDown(KEY_LEFT_SHIFT))
				(*text) += key;
			else
				(*text) += key - 'A' + 'a';
		}
		else if ((key >= '0' && key <= '9')||(key == '/' || key=='\\' || key=='.'))
		{
			(*text) += key;
		}
		if (IsKeyPressed(KEY_DELETE))
			(*text) = "";
		if (IsKeyPressed(KEY_BACKSPACE) && text->size()>0)
			text->pop_back();
	}
	isOn = CheckCollisionPointRec(GetMousePosition(), getPos());

}

bool TextEnter::press()
{
	if (isOn)
	{
		pressed = true;
		return true;
	}
	return false;
}

void TextEnter::unPress()
{
	pressed = false;
}

void TextEnter::draw()
{
	Element::draw();
	Rectangle pos=getPos();
	std::string textEnter = *text;
	if (isOn || pressed)
	{
		if ((int)(Element::timer * 2) % 2)
			textEnter += '_';
		if(isOn)
			DrawRectangleLinesEx(pos, 4, BLACK);

	}
	drawText(name.c_str(), pos.x, pos.y, textStandardSize, BLACK);
	int textY = textSize(name.c_str(), textStandardSize).y;
	drawText(textEnter.c_str(), pos.x, pos.y+textY, textStandardSize, BLACK);
}