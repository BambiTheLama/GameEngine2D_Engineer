#include "Element.h"

Element::Element(Rectangle pos)
{
	this->pos = pos;
}

Element::~Element()
{

}

void Element::update()
{

}

bool Element::press()
{
	return false;
}

void Element::unPress()
{

}

void Element::draw()
{
	DrawRectangleRec(pos, WHITE);
}