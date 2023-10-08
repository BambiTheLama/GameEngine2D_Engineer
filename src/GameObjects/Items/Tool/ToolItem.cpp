#include "ToolItem.h"
std::string ToolItem::description = "";

ToolItem::ToolItem(ToolItem& item) :Item(item),LinesCollider(item)
{
	sprite = new SpriteController(*item.sprite);
	this->useTimeMax=item.useTimeMax;
	useTime = 0;
	this->destroyType = item.destroyType;
	this->damage = item.damage;
	this->origin = item.origin;
	this->power = item.power;
}

ToolItem::ToolItem(nlohmann::json j):Item(j),LinesCollider(j)
{

	std::string path = "Resource/Items/" + std::string(j["Name"]) + ".png";
	sprite = new SpriteController(path.c_str());
	useTime = 0;
	origin = { 0,pos.width };
	if (j.contains("UseTime"))
		useTimeMax = j["UseTime"];
	else
		useTimeMax = 0.5;
	if (j.contains("Damage"))
		damage = j["Damage"];
	else
		damage = 1;

	if (j.contains("Power"))
		power = j["Power"];
	else
		power = 30;
	if (j.contains("DestoryType"))
		destroyType = (ToolType)j["DestoryType"];
	else
		destroyType = ToolType::NON;

	
}

ToolItem::~ToolItem()
{
	delete sprite;
}



void ToolItem::update(float deltaTime)
{
	if (useTime > 0)
	{
		useTime-=deltaTime;
		if (useTime <= 0)
			isUsing = false;
	}
	if (!isUsing)
		return;

	Rectangle pos = getPos();

	if (leftSide)
	{
		origin.x = pos.width;
		rotation -= deltaTime / useTimeMax * rotationAngle;
	}
	else
	{
		origin.x = 0;
		rotation += deltaTime / useTimeMax * rotationAngle;
	}

	LinesCollider::updateRotation(rotation , { 0,  0 },{0,-pos.height}, !leftSide);
	
	LinesCollider::update(deltaTime, this);

}



bool ToolItem::use(float deltaTime)
{
	if (useTime>0)
		return false;
	isUsing = true;
	useTime = useTimeMax;
	leftSide = !leftSide;
	rotation = cursorTarget({ pos.x,pos.y });
	if (leftSide)
		rotation += 220;
	else
		rotation -= 220;
	
	return true;
}
void ToolItem::draw()
{
	if (!inHand)
	{
		sprite->draw(getPos(), 0);
		return;
	}
	Rectangle textureSize = sprite->getTextureSize();
	Rectangle pos = getPos();
	if (useTime <= 0)
	{
		rotation = cursorTarget({ pos.x,pos.y });
		if (leftSide)
			rotation -= 40;
		else
			rotation += 40;
	}
	if (leftSide)
		textureSize.width = -textureSize.width;

	DrawTexturePro(sprite->getTexture(), textureSize, pos, origin, rotation, WHITE);
	if (collidersToDraw)
		LinesCollider::draw(this);
	

}

void ToolItem::drawAt(Rectangle pos)
{
	DrawTexturePro(sprite->getTexture(), sprite->getTextureSize(), pos, { 0,0 }, 0, WHITE);
	DrawRectangle(pos.x, pos.y, pos.width, pos.height*useTime/useTimeMax, { 159,159,159,159 });
}
std::string ToolItem::getDesctription()
{
	return std::string(TextFormat(description.c_str(), getName().c_str(), damage, power, useTimeMax));
}

void ToolItem::onCollisionHitable(HitAble* hit)
{
	hit->dealDamage(damage, invisibleFrame);
}
void ToolItem::onCollisionDestroyAble(DestroyAble* dest)
{

	dest->damageObject(power, destroyType);
	if (dest->isToolGoBack())
		isUsing = false;
}