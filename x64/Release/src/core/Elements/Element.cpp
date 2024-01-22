#include "Element.h"
float Element::timer = 0;
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
	DrawRectangleLinesEx(pos, 2, BLACK);
}