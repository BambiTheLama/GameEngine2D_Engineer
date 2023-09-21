#include "RectangleCollider.h"

RectangleCollider::RectangleCollider(Rectangle collision)
{
	this->collision = collision;
}

RectangleCollider::RectangleCollider(RectangleCollider& col):Collider(col)
{
	this->collision = col.collision;
}

void RectangleCollider::draw(GameObject* obj)
{
	Rectangle pos = obj->getPos();
	DrawRectangle(pos.x + collision.x, pos.y + collision.y, collision.width, collision.height, RED);
}
bool RectangleCollider::checkCollisionToObj(Collider* c, Vector2 thisPos, Vector2 otherPos)
{
	CollisionType type = c->getCollisionType();
	Rectangle pos = { collision.x + thisPos.x,collision.y + thisPos.y,collision.width,collision.height };
	if (type == CollisionType::Rec)
	{
		Rectangle pos2 = c->getCollisionPos();
		pos2.x += otherPos.x;
		pos2.y += otherPos.y;
		return CheckCollisionRecs(pos, pos2);
	}
	else if (type == CollisionType::Lines)
	{
		Vector2* points=c->getLines();
		if (!points)
			return false;
		int n=c->getHomManyLines();
		if (n <= 0)
			return false;
		Vector2* points2 = new Vector2[n];
		for (int i = 0; i < n; i++)
			points2[i] = { points[i].x + otherPos.x,points[i].y + otherPos.y };
		bool res = checkCollision(points2, n, pos);
		delete points2;
		printf("%d\n", (int)res);
		return res;
	}
	else if (type == CollisionType::Circle)
	{
		Vector2 circle=c->getCirlcePoint();
		float r = c->getRadius();
		circle.x += otherPos.x;
		circle.y += otherPos.y;
		return CheckCollisionCircleRec(circle, r, pos);
	}
	return false;	
}