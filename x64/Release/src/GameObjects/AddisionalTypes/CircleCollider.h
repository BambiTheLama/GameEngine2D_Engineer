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

	bool checkCollisionToObj(GameObject* thisObj, Collider* otherCollider, GameObject* otherObject);

	virtual Rectangle getCollisionPos();
};

