#include "CheckBox.h"

CheckBox::CheckBox(Rectangle pos, std::string text, bool* isPress) : Element(pos)
{
	this->isPress = isPress;
	this->text = text;
}

bool CheckBox::press()
{
	if (CheckCollisionPointRec(GetMousePosition(),getPos()))
	{
		(*isPress) = !(*isPress);
		return true;
	}
	return false;
}

void CheckBox::draw()
{
	Element::draw();
	Rectangle pos = getPos();
	int y = textSize(text.c_str(), textStandardSize).y;
	drawText(text.c_str(), pos.x, (pos.height-y)/2+pos.y, textStandardSize, BLACK);

	pos.x += pos.width - pos.height;
	pos.width = pos.height;
	DrawRectangleRec(pos, (*isPress) ? BLACK : WHITE);
}