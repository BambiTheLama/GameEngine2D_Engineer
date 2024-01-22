#pragma once
#include "Collider.h"
class RectangleCollider :
    public Collider
{
	Rectangle collision;
protected:
	RectangleCollider(RectangleCollider& col);
	void copyDataFrom(RectangleCollider& col);
public:
	RectangleCollider(Rectangle collision);

	RectangleCollider(ObjectType type, int ID);

	virtual void draw(GameObject* obj);

	virtual Rectangle getCollisionPos() { return collision; }

	virtual CollisionType getCollisionType() { return CollisionType::Rec; }

	bool checkCollisionToObj(GameObject* thisObj, Collider* otherCollider, GameObject* otherObject);

	void setCollision(Rectangle pos) { collision = pos; }
};

