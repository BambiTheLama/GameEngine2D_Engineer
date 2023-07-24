#include "ToolItem.h"


ToolItem::ToolItem(ToolItem& item) :Item(item)
{
	sprite = new SpriteController(*item.sprite);
	this->useTimeMax=item.useTimeMax;
	useTime = 0;
	this->destroyType = item.destroyType;
	this->power = item.power;
}

ToolItem::ToolItem(Rectangle pos, std::string name,ToolType destroyType,int power) :Item(pos, name)
{
	std::string path = "Resource/Items/" + name + ".png";
	sprite = new SpriteController(path.c_str());
	useTimeMax = 30;
	useTime = 0;
	this->destroyType = destroyType;
	this->power = power;
}
ToolItem::~ToolItem()
{
	delete sprite;
}
void ToolItem::update()
{
	if (useTime > 0)
	{
		useTime--;
	}

}

bool ToolItem::use()
{
	if (useTime>0)
		return false;

	Vector2 cursorPos = Game->getCursorPos();
	Rectangle pos = { cursorPos.x,cursorPos.y,1,1 };
	std::list<GameObject*> obj = Game->getObjects(pos);
	for (auto* o : obj)
	{
		if (!CheckCollisionRecs(pos, o->getPos())) continue;

		DestroyAble* toDestory = dynamic_cast<DestroyAble*>(o);
		if (toDestory != NULL)
		{
			toDestory->damageObject(power, destroyType);
		}
	}
	useTime = useTimeMax;
}
void ToolItem::draw()
{

	DrawTexturePro(sprite->getTexture(), sprite->getTextureSize(), getPos(), { 0,0 }, 0, WHITE);

}

void ToolItem::drawAt(Rectangle pos)
{
	DrawTexturePro(sprite->getTexture(), sprite->getTextureSize(), pos, { 0,0 }, 0, WHITE);
	DrawRectangle(pos.x, pos.y, pos.width, pos.height*useTime/useTimeMax, { 159,159,159,159 });
}
