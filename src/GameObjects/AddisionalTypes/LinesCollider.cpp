#include "LinesCollider.h"
#include "../../core/Scenes/GameScene.h"
#include "DestroyAble.h"
#include "HitAble.h"

LinesCollider::LinesCollider(LinesCollider& lines):Collider(lines)
{
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
LinesCollider::LinesCollider(Vector2* collision, int n, CollisionsCheckType collisionType):Collider(collisionType)
{
	if (startPoints)
		delete startPoints;
	if (this->points)
		delete this->points;
	nPoints = n;
	if (n <= 0 || !collision)
		return;
	startPoints = new Vector2[nPoints];
	this->points = new Vector2[nPoints];
	for (int i = 0; i < nPoints; i++)
	{
		startPoints[i] = collision[i];
		this->points[i] = collision[i];
	}

}

LinesCollider::LinesCollider(nlohmann::json j):Collider(j)
{
	if (j.contains("LineCollsionN"))
	{
		nPoints = j["LineCollsionN"];
		startPoints = new Vector2[nPoints];
		points = new Vector2[nPoints];
		for (int i = 0; i < nPoints; i++)
		{
			startPoints[i] = { 0,0 };
			points[i] = { 0,0 };
		}
		if (j.contains("Points"))
		{
			for (int i = 0; i < j["Points"].size(); i++)
			{
				Vector2 p;
				p.x = j["Points"][i][0];
				p.y = j["Points"][i][1];
				startPoints[i] = p;
				points[i] = p;
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

}
LinesCollider::~LinesCollider()
{
	if(startPoints)
		delete startPoints;
	if (points)
		delete this->points;
}
Vector2 origin;
void LinesCollider::draw(GameObject* obj)
{
	if (!points)
		return;
	Rectangle pos = obj->getPos();
	for (int i = 0; i < nPoints; i++)
	{
		Vector2 p1 = { points[i].x + pos.x,points[i].y + pos.y };
		Vector2 p2 = { points[(i + 1) % nPoints].x + pos.x,points[(i + 1) % nPoints].y + pos.y };
		DrawLineV(p1, p2, BLACK);
	}

	for (int i = 0; i < nPoints; i++)
	{
		Vector2 p1 = { points[i].x + pos.x,points[i].y + pos.y };
		DrawCircleV(p1, 1, BLUE);
	}
	DrawCircleV({pos.x+ origin.x,pos.y+ origin.y }, 2, RED);
	Rectangle col = getCollisionPos();
	col.x += pos.x;
	col.y += pos.y;
	DrawRectangleRec(col, BLACK);
}
void LinesCollider::updateRotation(float rotation, Vector2 origin,Vector2 moveBy, bool leftSide)
{
	this->origin = origin;
	rotation = ((rotation) * (PI / 180.0f));
	if (leftSide)
	{
		for (int i = 0; i < nPoints; i++)
		{
			points[i].x = moveBy.x + startPoints[i].x;
			points[i].y = moveBy.y + startPoints[i].y;
		}
	}
	else
	{
		for (int i = 0; i < nPoints; i++)
		{
			points[i].x = moveBy.x - startPoints[i].x;
			points[i].y = moveBy.y + startPoints[i].y;
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

Rectangle LinesCollider::getCollisionPos()
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
	return { minx,miny,maxx - minx,maxy - miny };
}

bool LinesCollider::checkCollisionToObj(Collider* c, Vector2 thisPos, Vector2 otherPos)
{
	Vector2* points = getLines();
	if (!points)
		return false;
	int n = getHomManyLines();
	if (n <= 0)
		return false;
	Vector2* points2 = new Vector2[n];
	for (int i = 0; i < n; i++)
		points2[i] = { points[i].x + thisPos.x,points[i].y + thisPos.y };
	bool res = false;
	CollisionType type = c->getCollisionType();

	if (type == CollisionType::Rec)
	{
		Rectangle pos = c->getCollisionPos();
		pos.x += otherPos.x;
		pos.y += otherPos.y;
		res = checkCollision(points2, n, pos);

	}
	else if (type == CollisionType::Lines)
	{
		Vector2* points3 = c->getLines();
		int n2 = c->getHomManyLines();
		if (points3 && n2 > 0)
		{
			Vector2* points4 = new Vector2[n2];
			for (int i = 0; i < n; i++)
				points4[i] = { points3[i].x + otherPos.x,points3[i].y + otherPos.y };
			res = checkCollision(points2, n, points4,n2);
			delete points4;
		}


	}
	else if (type == CollisionType::Circle)
	{
		Vector2 circle = c->getCirlcePoint();
		float r = c->getRadius();
		circle.x += otherPos.x;
		circle.y += otherPos.y;
		res = collideLinesCircle(circle, r, points2, n);
	}
	delete points2;
	return res;
}
