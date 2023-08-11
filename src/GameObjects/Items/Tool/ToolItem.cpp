#include "ToolItem.h"


ToolItem::ToolItem(ToolItem& item) :Item(item)
{
	sprite = new SpriteController(*item.sprite);
	this->useTimeMax=item.useTimeMax;
	useTime = 0;
	this->destroyType = item.destroyType;
	this->damage = item.damage;
	this->origin = item.origin;
	this->power = item.power;
	setStartPoints(item.startPoints);
}

ToolItem::ToolItem(Rectangle pos, std::string name,ToolType destroyType,int power) :Item(pos, name)
{
	std::string path = "Resource/Items/" + name + ".png";
	sprite = new SpriteController(path.c_str());
	useTimeMax = 20;
	useTime = 0;
	damage = 5;
	origin = { 0,pos.width };
	this->destroyType = destroyType;
	this->power = power;
	startPoints[0] = { pos.x ,pos.y };
	startPoints[1] = { pos.x + pos.width,pos.y };
	startPoints[2] = { pos.x + pos.width,pos.y + pos.height };
	startPoints[3] = { pos.x ,pos.y + pos.height };
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
	///Szukanie pozycji punktów do kolizji
	float k = ((rotation - 90) * (PI / 180.0f));
	Vector2 rotationPoint = origin;
	rotationPoint.x += pos.x;
	rotationPoint.y += pos.y;
	rotationPoint.y -= pos.height;
	if (faceSide == FaceSide::left)
	{
		rotationPoint.x -= pos.width;

	}
	k = ((rotation + 180) * (PI / 180.0f));

	Vector2 points[4];
	if (faceSide == FaceSide::left)
	{
		for (int i = 0; i < 4; i++)
		{
			points[i].x = pos.x + startPoints[i].x;
			points[i].y = pos.y + startPoints[i].y;
		}
	}
	else
	{
		for (int i = 0; i < 4; i++) 
		{
			points[i].x = pos.x - startPoints[i].x;
			points[i].y = pos.y + startPoints[i].y;
		}

	}

	///Wiliczanie wszystkich punktów obiektu
	for (int i = 0; i < 4; i++)
	{
		float x = cos(k) * (points[i].x - rotationPoint.x) - sin(k) * (points[i].y - rotationPoint.y) + rotationPoint.x;
		float y = sin(k) * (points[i].x - rotationPoint.x) + cos(k) * (points[i].y - rotationPoint.y) + rotationPoint.y;
		points[i].x = x;
		points[i].y = y;
	}
	///Minimum i maximum x i y
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
	///Pobranie wszystkich obiektów z sceny na pozycji gdzie mieœci siê narzêdzie
	Rectangle getObj = { minx,miny,maxx - minx,maxy - miny };
	std::list<GameObject*>objs = Game->getObjects(getObj,ObjectToGet::getNoBlocks);
	for (auto* o : objs)
	{
		HitAble* hit = dynamic_cast<HitAble*>(o);
		if (hit != NULL)
		{
			if (checkCollision(points, hit->getCollisionPos()))
			{
				hit->dealDamage(damage, 10);
			}
		}
		DestroyAble* toDestory = dynamic_cast<DestroyAble*>(o);
		if (toDestory != NULL)
		{
			Rectangle rec = toDestory->getCollisionPos();
			if (checkCollision(points, rec))
			{
				toDestory->damageObject(power, destroyType);
				if (toDestory->isToolGoBack())
					isUsing = false;
			}
		}



	}
	///Przekazanie punktów do zmiennych w klassie
	for (int i = 0; i < 4; i++)
		this->points[i] = points[i];

	

}



bool ToolItem::use()
{
	if (useTime>0)
		return false;
	isUsing = true;
	useTime = useTimeMax;
}
void ToolItem::draw()
{
	if (useTime<=0)
		return;
	Rectangle textureSize = sprite->getTextureSize();
	Rectangle pos = getPos();
	if(faceSide==FaceSide::left)
		textureSize.width = -textureSize.width;
	DrawTexturePro(sprite->getTexture(), textureSize, pos, origin, rotation, WHITE);
	if (collidersToDraw)
	{
		for (int i = 0; i < 4; i++)
			DrawLineV(points[i], points[(i + 1) % 4], BLACK);
		for (int i = 0; i < 4; i++)
		{
			DrawCircleV(points[i], 3, BLACK);
			DrawText(TextFormat("%d", i), points[i].x, points[i].y, 16, RED);
		}
	}

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
	for (int i = 0; i < 4; i++)
		this->startPoints[i] = startPoints[i];
}