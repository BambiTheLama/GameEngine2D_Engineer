#pragma once
#include "Collider.h"
class CircleCollider :
    public Collider
{
	Vector2 p;
	float r;
protected:
	CircleCollider(CircleCollider& c);
public:
	CircleCollider(Vector2 p, float r);

	virtual void draw(GameObject* obj);

	virtual int getRadius() { return r; }

	virtual Vector2 getCirlcePoint() { return p; }

	virtual CollisionType getCollisionType() { return CollisionType::Circle; }

	bool checkCollisionToObj(Collider* c, Vector2 thisPos, Vector2 otherPos);

	virtual Rectangle getMaxRectangle();
};

