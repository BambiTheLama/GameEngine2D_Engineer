#include "RectangleCollider.h"
#include "../GameObject.h"

RectangleCollider::RectangleCollider(Rectangle collision)
{
	this->collision = collision;
}
void RectangleCollider::copyDataFrom(RectangleCollider& col)
{
	this->collision = col.collision;
}
RectangleCollider::RectangleCollider(RectangleCollider& col):Collider(col)
{
	copyDataFrom(col);
}

RectangleCollider::RectangleCollider(ObjectType type, int ID)
{
	RectangleCollider* dest = NULL;
	GameObject* obj = getObjFromFactory(type,ID);
	if (obj)
	{
		dest = dynamic_cast<RectangleCollider*>(obj);
		if (dest)
			copyDataFrom(*dest);
		delete obj;
	}
}

void RectangleCollider::draw(GameObject* obj)
{
	Rectangle pos = obj->getPos();
	DrawRectangle(pos.x + collision.x, pos.y + collision.y, collision.width, collision.height, RED);
}
bool RectangleCollider::checkCollisionToObj(GameObject* thisObj, Collider* otherCollider, GameObject* otherObject)
{
	CollisionType type = otherCollider->getCollisionType();
	Rectangle thisPos = thisObj->getPos();
	Rectangle otherPos = otherObject->getPos();
	Rectangle pos = { collision.x + thisPos.x,collision.y + thisPos.y,collision.width,collision.height };
	if (type == CollisionType::Rec)
	{
		Rectangle pos2 = otherCollider->getCollisionPos();
		pos2.x += otherPos.x;
		pos2.y += otherPos.y;
		return CheckCollisionRecs(pos, pos2);
	}
	else if (type == CollisionType::Lines)
	{
		Vector2* points= otherCollider->getLines();
		if (!points)
			return false;
		int n= otherCollider->getHomManyLines();
		if (n <= 0)
			return false;
		Vector2* points2 = new Vector2[n];
		for (int i = 0; i < n; i++)
			points2[i] = { points[i].x + otherPos.x,points[i].y + otherPos.y };
		bool res = checkCollision(points2, n, pos);
		delete points2;
		return res;
	}
	else if (type == CollisionType::Circle)
	{
		Vector2 circle= otherCollider->getCirlcePoint();
		float r = otherCollider->getRadius();
		circle.x += otherPos.x;
		circle.y += otherPos.y;
		return CheckCollisionCircleRec(circle, r, pos);
	}
	return false;	
}