#include "CircleCollider.h"
CircleCollider::CircleCollider(Vector2 p, float r)
{
	this->p = p;
	this->r = r;
}

CircleCollider::CircleCollider(CircleCollider& c)
{
	this->p = c.p;
	this->r = c.r;
}

void CircleCollider::draw(GameObject* obj)
{
	Rectangle pos = obj->getPos();
	DrawCircle(pos.x + p.x, pos.y + p.y, r, RED);
}

bool CircleCollider::checkCollisionToObj(GameObject* thisObj, Collider* otherCollider, GameObject* otherObject)
{
	CollisionType type = otherCollider->getCollisionType();
	Vector2 circle = getCirlcePoint();
	float r = getRadius();
	Rectangle thisPos = thisObj->getPos();
	Rectangle otherPos = otherObject->getPos();
	circle.x += thisPos.x;
	circle.y += thisPos.y;

	if (type == CollisionType::Rec)
	{
		Rectangle pos = otherCollider->getCollisionPos();
		pos.x += otherPos.x;
		pos.y += otherPos.y;
		return CheckCollisionCircleRec(circle, r, pos);
	}
	else if (type == CollisionType::Lines)
	{
		Vector2* points = otherCollider->getLines();
		if (!points)
			return false;
		int n = otherCollider->getHomManyLines();
		if (n <= 0)
			return false;
		Vector2* points2 = new Vector2[n];
		for (int i = 0; i < n; i++)
			points2[i] = { points[i].x + otherPos.x,points[i].y + otherPos.y };
		bool res = collideLinesCircle(circle, r, points2, n);
		delete points2;
		return res;
	}
	else if (type == CollisionType::Circle)
	{
		Vector2 circle2 = otherCollider->getCirlcePoint();
		float r2 = otherCollider->getRadius();
		circle2.x += otherPos.x;
		circle2.y += otherPos.y;
		return CheckCollisionCircles(circle2, r2, circle, r);
	}
	return false;
}
Rectangle CircleCollider::getCollisionPos()
{
	Vector2 circle = getCirlcePoint();
	float r = getRadius();
	return { circle.x - r,circle.y - r,r + r,r + r };
}