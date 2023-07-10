#include "Item.h"
Item::Item(Item& obj) :GameObject(obj)
{

}
Item::Item(Rectangle pos, std::string name):GameObject(pos,name)
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

void Item::drawAt(Rectangle pos)
{

}

bool Item::use()
{
	return false;
}