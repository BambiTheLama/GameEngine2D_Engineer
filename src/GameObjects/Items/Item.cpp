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

void Item::update(float deltaTime)
{

}

void Item::draw()
{

}

void Item::drawAt(Rectangle pos)
{

}

bool Item::use(float deltaTime)
{
	return false;
}
void Item::saveToJson(nlohmann::json j)
{
	j[getID()]["ItemType"] = getItemType();
}