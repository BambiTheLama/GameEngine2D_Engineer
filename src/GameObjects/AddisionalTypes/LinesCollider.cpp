#include "LinesCollider.h"
#include "../../core/Scenes/GameScene.h"
#include "DestroyAble.h"
#include "HitAble.h"

LinesCollider::LinesCollider(LinesCollider& lines)
{
	type = lines.type;
	nPoints = lines.nPoints;
	startPoints = new Vector2[nPoints];
	points = new Vector2[nPoints];
	for (int i = 0; i < nPoints; i++)
	{
		startPoints[i] = lines.startPoints[i];
		points[i] = lines.points[i];
	}
	rotation = lines.rotation;
}

LinesCollider::LinesCollider(CollisionsCheckType type)
{
	this->type = type;
}
LinesCollider::LinesCollider(nlohmann::json j, int ID)
{
	if (j[ID].contains("LineCollsionN"))
	{
		nPoints = j[ID]["LineCollsionN"];
		startPoints = new Vector2[nPoints];
		points = new Vector2[nPoints];
		for (int i = 0; i < nPoints; i++)
		{
			if (j[ID].contains(("Point" + std::to_string(i))))
			{
				Vector2 p;
				p.x = j[ID][("Point" + std::to_string(i))][0];
				p.y = j[ID][("Point" + std::to_string(i))][1];
				startPoints[i] = p;
				points[i] = p;
			}
			else
			{
				startPoints[i] = {0,0};
				points[i] = {0,0};
			}

		}
	}
	else
	{
		nPoints = 4;
		startPoints = new Vector2[4];
		points = new Vector2[4];
		Rectangle pos = { 0,0,16,16 };
		GameObject* obj = dynamic_cast<GameObject*>(this);
		if (obj)
			pos = obj->getPos();
		points[0] = { 0,0 };
		points[1] = { pos.width,0 };
		points[2] = { pos.width,pos.height };
		points[3] = { 0,pos.height };
		for (int i = 0; i < 4; i++)
			points[i] = startPoints[i];
	}
	if (j[ID].contains("CollisionsCheckType"))
	{
		this->type = (CollisionsCheckType)j[ID]["CollisionsCheckType"];
	}
	else
	{
		this->type = CollisionsCheckType::All;
	}
}
LinesCollider::~LinesCollider()
{
	if(startPoints)
		delete startPoints;
	if (points)
		delete this->points;
}
void LinesCollider::addLines(int n, Vector2* points)
{
	if (startPoints)
		delete startPoints;
	if (points)
		delete this->points;
	nPoints = n;
	startPoints = new Vector2[nPoints];
	this->points = new Vector2[nPoints];
	for (int i = 0; i < nPoints; i++)
		startPoints[i] = points[i];
}
void LinesCollider::draw()
{
	for (int i = 0; i < nPoints; i++)
		DrawLineV(points[i], points[(i + 1) % nPoints], BLACK);
	for (int i = 0; i < nPoints; i++)
	{
		DrawCircleV(points[i], 1, BLUE);
	}
}
void LinesCollider::updateRotation(float rotation, Vector2 origin, Vector2 pos, bool leftSide)
{
	rotation = ((rotation) * (PI / 180.0f));
	if (leftSide)
	{
		for (int i = 0; i < nPoints; i++)
		{
			points[i].x = pos.x + startPoints[i].x;
			points[i].y = pos.y + startPoints[i].y;
		}
	}
	else
	{
		for (int i = 0; i < nPoints; i++)
		{
			points[i].x = pos.x - startPoints[i].x;
			points[i].y = pos.y + startPoints[i].y;
		}
	}
	for (int i = 0; i < nPoints; i++)
	{
		float x = cos(rotation) * (points[i].x - origin.x) - sin(rotation) * (points[i].y - origin.y) + origin.x;
		float y = sin(rotation) * (points[i].x - origin.x) + cos(rotation) * (points[i].y - origin.y) + origin.y;
		points[i].x = x;
		points[i].y = y;
	}

}

void LinesCollider::update(float deltaTime)
{
	float minx = points[0].x;
	float maxx = points[0].x;
	float miny = points[0].y;
	float maxy = points[0].y;
	for (int i = 1; i < nPoints; i++)
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
	std::list<GameObject*>objs = Game->getObjects(getObj, ObjectToGet::getNoBlocks);
	GameObject* thisObj = dynamic_cast<GameObject*>(this);
	if (thisObj)
		objs.remove(thisObj);
	if (type == CollisionsCheckType::All)
	{
		for (auto* o : objs)
		{
			HitAble* hit = dynamic_cast<HitAble*>(o);
			if (hit)
			{
				if (checkCollision(points, hit->getCollisionPos()))
				{
					onCollisionHitable(hit);
				}
			}
			DestroyAble* toDestory = dynamic_cast<DestroyAble*>(o);
			if (toDestory)
			{
				Rectangle rec = toDestory->getCollisionPos();
				if (checkCollision(points, rec))
				{
					onCollisionDestroyAble(toDestory);
				}
			}
		}
	}
	else if (type == CollisionsCheckType::HitAbleOnly)
	{
		for (auto* o : objs)
		{
			HitAble* hit = dynamic_cast<HitAble*>(o);
			if (hit)
			{
				if (checkCollision(points, hit->getCollisionPos()))
				{
					onCollisionHitable(hit);
				}
			}
		}
	}
	else if (type == CollisionsCheckType::DestoryAbleOnly)
	{
		for (auto* o : objs)
		{
			DestroyAble* toDestory = dynamic_cast<DestroyAble*>(o);
			if (toDestory)
			{
				Rectangle rec = toDestory->getCollisionPos();
				if (checkCollision(points, rec))
				{
					onCollisionDestroyAble(toDestory);
				}
			}
		}
	}
	
}

void LinesCollider::onCollisionHitable(HitAble* hit)
{

}
void LinesCollider::onCollisionDestroyAble(DestroyAble* dest)
{

}