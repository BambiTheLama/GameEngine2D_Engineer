#include "Item.h"
Item::Item(Item& obj) :GameObject(obj)
{

}
Item::Item(Rectangle pos):GameObject(pos)
{

}
Item::~Item()
{

}

void Item::update()
{

}

void Item::draw()
{

}
bool Item::use()
{
	return false;
}