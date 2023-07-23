#include "ToolItem.h"


ToolItem::ToolItem(ToolItem& item) :Item(item)
{
	sprite = new SpriteController(*item.sprite);
}

ToolItem::ToolItem(Rectangle pos, std::string name) :Item(pos, name)
{
	std::string path = "Resource/Items/" + name + ".png";
	sprite = new SpriteController(path.c_str());
}
ToolItem::~ToolItem()
{
	delete sprite;
}
bool ToolItem::use()
{
	return false;
}
void ToolItem::draw()
{

	DrawTexturePro(sprite->getTexture(), sprite->getTextureSize(), getPos(), { 0,0 }, 0, WHITE);

}

void ToolItem::drawAt(Rectangle pos)
{
	DrawTexturePro(sprite->getTexture(), sprite->getTextureSize(), pos, { 0,0 }, 0, WHITE);
}
