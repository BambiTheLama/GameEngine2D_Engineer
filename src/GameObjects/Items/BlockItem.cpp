#include "BlockItem.h"


BlockItem::BlockItem(BlockItem& item):Item(item)
{
	stackMaxSize = item.stackMaxSize;
	sprite = new SpriteController(*item.sprite);
}

BlockItem::BlockItem(Rectangle pos, std::string name, std::string path, int stackSize) :Item(pos, name)
{
	this->stackMaxSize = stackSize;
	this->stackSize = 1;
	sprite = new SpriteController(path.c_str());
}

BlockItem::~BlockItem()
{
	delete sprite;
}

bool BlockItem::use()
{
	return false;
}

void BlockItem::draw()
{
	drawAt(getPos());
}

void BlockItem::drawAt(Rectangle pos)
{
	DrawTexturePro(sprite->getTexture(), sprite->getTextureSize(), pos, { 0,0 }, 0, WHITE);
}