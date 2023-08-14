#include "ToolItem.h"


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

ToolItem::ToolItem(Rectangle pos, std::string name,ToolType destroyType,int power) :Item(pos, name),LinesCollider(CollisionsCheckType::All)
{
	std::string path = "Resource/Items/" + name + ".png";
	sprite = new SpriteController(path.c_str());
	useTimeMax = 0.5f;
	useTime = 0;
	damage = 5;
	origin = { 0,pos.width };
	this->destroyType = destroyType;
	this->power = power;

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
	origin.x = 0;
	rotation = 0;
	const float rotationAngle = 120;
	///Wiliczanie obeotu narzêdzia
	switch (faceSide)
	{
	case FaceSide::left:
		rotation = 320;
		if (useTime > 0)
			rotation += (float)useTime / (float)useTimeMax * rotationAngle;
		else
			rotation += rotationAngle;
		origin.x = pos.width;
		break;
	case FaceSide::right:
		rotation = 30;
		if (useTime > 0)
			rotation -= (float)useTime / (float)useTimeMax * rotationAngle;
		else
			rotation -= rotationAngle;
		break;
	case FaceSide::up:
		rotation = 0;
		if (useTime > 0)
			rotation -= (float)useTime / (float)useTimeMax * rotationAngle;
		else
			rotation -= rotationAngle;
		break;
	case FaceSide::down:
		rotation = 200;
		if (useTime > 0)
			rotation -= (float)useTime / (float)useTimeMax * rotationAngle;
		else
			rotation -= rotationAngle;
		break;
	}
	if (!isUsing)
		return;

	LinesCollider::updateRotation(rotation + 180, { pos.x,pos.y }, { pos.x,pos.y }, faceSide == FaceSide::left);
	
	LinesCollider::update(deltaTime);

}



bool ToolItem::use(float deltaTime)
{
	if (useTime>0)
		return false;
	isUsing = true;
	useTime = useTimeMax;
}
void ToolItem::draw()
{
	if (!inHand)
	{
		sprite->draw(getPos(), 0);
		return;
	}
	if (useTime<=0)
		return;
	Rectangle textureSize = sprite->getTextureSize();
	Rectangle pos = getPos();
	if(faceSide==FaceSide::left)
		textureSize.width = -textureSize.width;
	DrawTexturePro(sprite->getTexture(), textureSize, pos, origin, rotation, WHITE);
	if (collidersToDraw)
		LinesCollider::draw();
	

}

void ToolItem::drawAt(Rectangle pos)
{
	DrawTexturePro(sprite->getTexture(), sprite->getTextureSize(), pos, { 0,0 }, 0, WHITE);
	DrawRectangle(pos.x, pos.y, pos.width, pos.height*useTime/useTimeMax, { 159,159,159,159 });
}
std::string ToolItem::getDesctription()
{
	return getName() + "\n" + "tool power" + std::to_string(power) + "";
}
void ToolItem::setStartPoints(Vector2 startPoints[4])
{
	addLines(4, startPoints);
}

void ToolItem::onCollisionHitable(HitAble* hit)
{
	hit->dealDamage(damage, 2);
}
void ToolItem::onCollisionDestroyAble(DestroyAble* dest)
{
	dest->damageObject(power, destroyType);
	if (dest->isToolGoBack())
		isUsing = false;
}