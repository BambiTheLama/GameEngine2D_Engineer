#include "Collider.h"
#include "../../core/Scenes/GameScene.h"
#include <iostream>

Collider::Collider(Collider& col)
{
	this->type = col.type;
}

Collider::Collider(CollisionsCheckType type)
{
	this->type = type;
}

Collider::Collider(nlohmann::json j)
{
	if (j.contains("CollisionsCheckType"))
	{
		this->type = (CollisionsCheckType)j["CollisionsCheckType"];
	}
	else
	{
		this->type = CollisionsCheckType::All;
	}
}

bool Collider::checkCollisionToObj(Collider *c,Vector2 thisPos,Vector2 otherPos)
{
	return false;
}

bool Collider::isCollidingWithSomething()
{
	GameObject* obj = dynamic_cast<GameObject*>(this);
	if (!obj)
		return false;
	std::list<GameObject*> objects = Game->getObjects(obj->getPos());
	objects.remove(obj);

	
	for (GameObject* o : objects)
	{
		if (!o->isColliding())
			continue;
		Collider* collider = dynamic_cast<Collider*>(o);
		if (!collider)
			continue;
		Rectangle pos1 = obj->getPos();
		Rectangle pos2 = o->getPos();
		if (checkCollisionToObj(collider, { pos1.x,pos1.y }, { pos2.x,pos2.y }))
			return true;
	}
	return false;
}

void Collider::update(float deltaTime, GameObject* obj)
{
	Rectangle pos = obj->getPos();
	Rectangle getObj = getCollisionPos();
	getObj.x += pos.x;
	getObj.y += pos.y;
	std::list<GameObject*>objs = Game->getObjects(getObj, ObjectToGet::getNoBlocks);
	objs.remove(obj);
	for (auto i : objectsToIgnore)
		objs.remove(i);

	if (type == CollisionsCheckType::All)
	{
		for (auto* o : objs)
		{
			HitAble* hit = dynamic_cast<HitAble*>(o);
			Collider* col = dynamic_cast<Collider*>(o);
			if (hit)
			{
				if (col)
				{
					Rectangle pos = obj->getPos();
					Rectangle pos2 = o->getPos();
					if (checkCollisionToObj(col, {pos.x,pos.y},{pos2.x,pos2.y}))
						onCollisionHitable(hit);

				}
			}
			DestroyAble* toDestory = dynamic_cast<DestroyAble*>(o);
			if (toDestory)
			{
				if (col)
				{
					Rectangle pos = obj->getPos();
					Rectangle pos2 = o->getPos();
					if (checkCollisionToObj(col, { pos.x,pos.y }, { pos2.x,pos2.y }))
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
				Collider* col = dynamic_cast<Collider*>(o);
				if (col)
				{
					Rectangle pos = obj->getPos();
					Rectangle pos2 = o->getPos();
					if (checkCollisionToObj(col, { pos.x,pos.y }, { pos2.x,pos2.y }))
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
				Collider* col = dynamic_cast<Collider*>(o);
				if (col)
				{
					Rectangle pos = obj->getPos();
					Rectangle pos2 = o->getPos();
					if (checkCollisionToObj(col, { pos.x,pos.y }, { pos2.x,pos2.y }))
						onCollisionDestroyAble(toDestory);
				}
			}
		}
	}
}

void Collider::addObjToIgnore(GameObject* ignore)
{
	objectsToIgnore.push_back(ignore);
}

void Collider::removeObjectToIgnore(GameObject* ignore)
{
	objectsToIgnore.remove(ignore);
}

void Collider::clearListToIgnore()
{
	objectsToIgnore.clear();
}

bool checkCollision(GameObject* obj)
{
	std::list<GameObject*> objs = Game->getObjects(obj->getPos());
	objs.remove(obj);
	for (GameObject* o : objs)
		if (o->isColliding())
		{
			if (CheckCollisionRecs(o->getPos(), obj->getPos()))
				return true;
		}

	return false;
}
bool isOnLine(float p1, float p2, float x)
{
	if (p1 > p2)
	{
		return x >= p2 && x <= p1;
	}
	else
	{
		return x >= p1 && x <= p2;
	}
}

bool checkCollision(Vector2* points, int n, Rectangle pos)
{
	for (int i = 0; i < n; i++)
	{
		Vector2 p1 = points[i];
		Vector2 p2 = points[(i + 1) % n];

		if (CheckCollisionLines(p1, p2, { pos.x,pos.y }, { pos.x,pos.y + pos.height }, NULL))
		{
			return true;
		}
		if (CheckCollisionLines(p1, p2, { pos.x + pos.width,pos.y }, { pos.x + pos.width,pos.y + pos.height }, NULL))
		{
			return true;
		}
		if (CheckCollisionLines(p1, p2, { pos.x ,pos.y }, { pos.x + pos.width,pos.y }, NULL))
		{
			return true;
		}
		if (CheckCollisionLines(p1, p2, { pos.x,pos.y+pos.height }, { pos.x + pos.width,pos.y + pos.height }, NULL))
		{
			return true;
		}
		if (CheckCollisionLines(p1, p2, { pos.x ,pos.y }, { pos.x + pos.width,pos.y + pos.height }, NULL));
		{
			return true;
		}
		if (CheckCollisionLines(p1, p2, { pos.x,pos.y + pos.height }, { pos.x + pos.width,pos.y }, NULL));
		{
			return true;
		}

	}
	return false;
}
void LineData::calculateAB()
{
	if (x1 - x2 != 0)
		a = (y1 - y2) / (x1 - x2);
	else
		a = INT32_MAX;

	b = y1 - a * x1;
	if (x1 > x2)
	{
		float x = x2;
		x2 = x1;
		x1 = x;
	}
	if (y1 > y2)
	{
		float y = y2;
		y2 = y1;
		y1 = y;
	}
}

bool LineData::checkLines(LineData l)
{
	float x = (b - l.b) / (l.a - a);
	//float y = a * x + b;

	return (x1 <= x && x2 >= x && l.x1 <= x && l.x2 >= x);

}
bool checkCollision(Vector2* points, int n, Vector2* points2, int n2)
{
	LineData* firstObj = new LineData[n];
	LineData* secObj = new LineData[n2];
	for (int i = 0; i < n; i++)
	{
		firstObj[i].x1 = points[i].x;
		firstObj[i].y1 = points[i].y;
		firstObj[i].x2 = points[(i + 1) % n].x;
		firstObj[i].y2 = points[(i + 1) % n].y;
		firstObj[i].calculateAB();
	}
	for (int i = 0; i < n2; i++)
	{
		secObj[i].x1 = points2[i].x;
		secObj[i].y1 = points2[i].y;
		secObj[i].x2 = points2[(i + 1) % n2].x;
		secObj[i].y2 = points2[(i + 1) % n2].y;
		secObj[i].calculateAB();
	}
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n2; j++)
			if (firstObj[i].checkLines(secObj[j]))
			{
				delete firstObj;
				delete 	secObj;
				return true;
			}
	delete firstObj;
	delete secObj;
	return false;
}

float distance(float x1, float y1, float x2, float y2) {
	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

bool collideLineCircle(Vector2 v, float radius, Vector2 p1, Vector2 p2) {
	float dx = p2.x - p1.x;
	float dy = p2.y - p1.y;
	float len = distance(p1.x, p1.y, p2.x, p2.y);
	float dot = (((v.x - p2.x) * (p1.x - p2.x)) + ((v.y - p2.y) * (p1.y - p2.y))) / pow(len, 2);

	float closestX = p2.x + (dot * (p1.x - p2.x));
	float closestY = p2.y + (dot * (p1.y - p2.y));

	if (!CheckCollisionPointLine({ closestX,closestY }, p1, p2, 1))
		return false;
	float distX = closestX - v.x;
	float distY = closestY - v.y;
	float distance = sqrt((distX * distX) + (distY * distY));
	return distance <= radius;
}
bool collideLinesCircle(Vector2 v, float radius, Vector2* points, int n)
{
	if (!points)
		return false;
	for (int i = 0; i < n; i++)
		if (collideLineCircle(v, radius, points[i], points[(i + 1) % n]))
			return true;
	return false;
}