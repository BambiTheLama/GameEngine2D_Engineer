#include "CheckBoxOpenElements.h"

CheckBoxOpenElements::CheckBoxOpenElements(Rectangle pos, std::string text, bool* isPress):
	CheckBox(pos,text,isPress)
{
	componetPos = pos;
}

CheckBoxOpenElements::~CheckBoxOpenElements()
{

}

void CheckBoxOpenElements::updatePos()
{
	componetPos = Element::getPos();
	if (up)
	{
		Rectangle pos = up->getPos();
		componetPos.y = pos.y + pos.height;
		componetPos.x = pos.x;
		componetPos.width = pos.width;
		setPos(componetPos);
	}

	componetPos.x += 20;
	componetPos.width -= 20;
	if (openElements)
	{
		for (auto* e : elements)
		{
			Rectangle pos = e->getPos();
			e->setPos({ componetPos.x,componetPos.y+componetPos.height,componetPos.width,pos.height });
			e->updatePos();
			componetPos.height += pos.height;
		}
	}
	componetPos.x -= 20;
	componetPos.width += 20;
	if(down)
		down->updatePos();
}

void CheckBoxOpenElements::update()
{
	if (!*isPress)
		return;
	if (openElements)
	{
		for (auto* e : elements)
			e->update();
	}
}

bool CheckBoxOpenElements::press()
{
	if (!*isPress)
		return false;
	Rectangle pos = Element::getPos();
	if (CheckCollisionPointRec(GetMousePosition(), {pos.x + pos.width, pos.y, pos.height, pos.height}))
	{
		openElements = !openElements;
		updatePos();
		return true;
	}
	if (openElements)
	{
		for (auto* e : elements)
			if (e->press())
			{
				lastPress = e;
				return true;
			}

	}
	return false;
}

void CheckBoxOpenElements::unPress()
{
	if (lastPress)
	{
		lastPress->unPress();
		lastPress = NULL;
	}
}

void CheckBoxOpenElements::draw()
{
	if (!*isPress)
		return;
	CheckBox::draw();
	Rectangle pos = Element::getPos();
	DrawRectangle(pos.x + pos.width, pos.y, pos.height, pos.height, openElements?GREEN: RED);
	if (openElements)
	{
		for (auto* e : elements)
			e->draw();
	}

}

void CheckBoxOpenElements::reloadData()
{
	for (auto* e : elements)
		e->reloadData();
}