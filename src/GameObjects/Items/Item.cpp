#include "Item.h"
Item::Item(Item& obj) :GameObject(obj)
{
	itemName = obj.itemName;
}
Item::Item(Rectangle pos, std::string name):GameObject(pos,name)
{
	itemName = name;
}

Item::Item(nlohmann::json j, int ID):GameObject(j,ID)
{
	itemName = j[ID]["Name"];
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

void Item::drawDescription(int x, int y)
{
	std::string description = getDesctription();
	Vector2 descriptionSize = getItemDescriptionSize();
	Rectangle dest = { x - 10, y, descriptionSize.x + 20, descriptionSize.y };
	DrawRectangleRounded(dest, 0.32137, 10, BLUE);
	DrawRectangleRoundedLines(dest, 0.32137, 10, 2, BLACK);
	//DrawRectangleRec(dest, BLUE);
	drawText(description.c_str(), x, y + 10, textStandardSize, BLACK);
}
Vector2 Item::getItemDescriptionSize()
{
	Vector2 size = textSize(getDesctription().c_str(), textStandardSize);
	size.y += 20;
	return size;
}
void Item::loadLangue(nlohmann::json j)
{
	if (j.contains(name))
	{
		itemName = j[name];
	}
	else
		itemName = name;
}