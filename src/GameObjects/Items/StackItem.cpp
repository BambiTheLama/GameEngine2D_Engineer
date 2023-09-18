#include "StackItem.h"

std::string StackItem::description="";

StackItem::StackItem(StackItem& item):Item(item)
{
	stackMaxSize = item.stackMaxSize;
	this->stackSize = item.stackSize;
	sprite = new SpriteController(*item.sprite);
}

StackItem::StackItem(Rectangle pos, std::string name, int stackSize) :Item(pos, name)
{
	this->stackMaxSize = stackSize;
	this->stackSize = 1;
	std::string path = "Resource/Items/" + name + ".png";
	sprite = new SpriteController(path.c_str());
}
StackItem::StackItem(nlohmann::json j, int ID) :Item(j, ID)
{
	this->stackSize = 1;
	if (j[ID].contains("StackSize"))
		stackMaxSize = j[ID]["StackSize"];
	else
		stackMaxSize = 100;
	std::string path = "Resource/Items/" + std::string(j[ID]["Name"]) + ".png";
	sprite = new SpriteController(path.c_str());

}

StackItem::~StackItem()
{
	delete sprite;
}

bool StackItem::use(float deltaTime)
{
	return false;
}

void StackItem::draw()
{
	
	DrawTexturePro(sprite->getTexture(), sprite->getTextureSize(), getPos(), {0,0}, 0, WHITE);

}

void StackItem::drawAt(Rectangle pos)
{
	DrawTexturePro(sprite->getTexture(), sprite->getTextureSize(), pos, { 0,0 }, 0, WHITE);
}

bool StackItem::addToStack(Item* item)
{
	if (getID() != item->getID())
		return false;
	int canTake = stackMaxSize - stackSize;
	if (canTake >= item->getStackSize())
	{
		stackSize += item->getStackSize();
		item->removeFromStack(item->getStackSize());
		return true;
	}
	else
	{
		item->removeFromStack(canTake);
		stackSize = stackMaxSize;
	}
	return false;
}

std::string StackItem::getDesctription()
{
	return std::string(TextFormat(description.c_str(), getName().c_str(), stackSize));
}