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

	Rectangle pos = getPos();
	origion.x = 0;
	rotation = 0;
	const float rotationAngle = 120;

	switch (faceSide)
	{
	case FaceSide::left:
		rotation = 320;
		if (useTime > 0)
			rotation += (float)useTime / (float)useTimeMax * rotationAngle;
		else
			rotation += rotationAngle;
		origion.x = pos.width;
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
	if (useTime > 0)
	{
		float k = ((rotation - 90) * (PI / 180.0f));
		Vector2 rotationPoint = origion;
		rotationPoint.x += pos.x;
		rotationPoint.y += pos.y;
		rotationPoint.y -= pos.height;
		if (faceSide == FaceSide::left)
		{
			rotationPoint.x -= pos.width;
			k = ((rotation + 180) * (PI / 180.0f));
		}
		else
		{
			k = ((rotation - 90) * (PI / 180.0f));
		}


		Vector2 points[4] = { {pos.x,pos.y},
			{pos.x + pos.width,pos.y},
			{pos.x + pos.width,pos.y + pos.height},
			{pos.x, pos.y + pos.height} };
		
		for (int i = 0; i < 4; i++)
		{
			float x = cos(k) * (points[i].x - rotationPoint.x) - sin(k) * (points[i].y - rotationPoint.y) + rotationPoint.x;
			float y = sin(k) * (points[i].x - rotationPoint.x) + cos(k) * (points[i].y - rotationPoint.y) + rotationPoint.y;
			points[i].x = x;
			points[i].y = y;
		}
		int minx = points[0].x;
		int maxx = points[0].x;
		int miny = points[0].y;
		int maxy = points[0].y;
		for (int i = 1; i < 4; i++)
		{
			if (minx > points[i].x)
				minx = points[i].x;
			if (miny > points[i].y)
				miny = points[i].y;
			if (maxx < points[i].x)
				maxx = points[i].x;
			if (maxy < points[i].y)
				maxy = points[i].y;
		}
		Rectangle getObj = { minx,miny,maxx - minx,maxy - miny };
		std::list<GameObject*>objs=Game->getObjects(getObj,ObjectToGet::getNoBlocks);
		for (auto* o : objs)
		{
			HitAble* hit = dynamic_cast<HitAble*>(o);
			if (hit == NULL)
				continue;
			if (checkCollision(points, hit->getCollisionPos()))
			{
				hit->dealDamage(damage, 10);
			}
			
			
			
		}
		for (int i = 0; i < 4; i++)
			this->points[i] = points[i];

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
	Rectangle textureSize = sprite->getTextureSize();
	Rectangle pos = getPos();
	if(faceSide==FaceSide::left)
		textureSize.width = -textureSize.width;
	DrawTexturePro(sprite->getTexture(), textureSize, pos, origion, rotation, WHITE);
	for (int i = 0; i < 4; i++)
		DrawCircleV(points[i], 3, BLACK);
	for (int i = 0; i < 4; i++)
		DrawLineV(points[i], points[(i+1)%4], BLACK);
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