#pragma once
#include "raylib.h"
#include "../GameObject.h"
class Collider
{
	Rectangle collision;
public:
	Collider(Rectangle col);

	Collider(Collider& collder);

	Rectangle getCollisionPos(GameObject* obj);

	bool isCollidingWithSomething(GameObject* obj);

	void draw(GameObject* obj)
	{
		Rectangle pos = obj->getPos();
		DrawRectangle(pos.x + collision.x, pos.y + collision.y, collision.width, collision.height, RED);
	}
};

