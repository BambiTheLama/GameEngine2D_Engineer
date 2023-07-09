#include "Collider.h"
#include "../../core/Scenes/GameScene.h"
#include <iostream>
Collider::Collider(Rectangle col)
{
	collision = col;
}

Collider::Collider(Collider& col)
{
	collision = col.collision;
}

Rectangle Collider::getCollisionPos(GameObject* obj)
{
	Rectangle pos = obj->getPos();
	return { pos.x + collision.x,pos.y + collision.y,collision.width,collision.height };
}

bool Collider::isCollidingWithSomething(GameObject* obj)
{
	Rectangle pos = obj->getPos();
	Rectangle collisonPos = { pos.x + collision.x,pos.y + collision.y,collision.width,collision.height };
	std::list<GameObject*> objects = Game->getObjects(collisonPos);

	objects.remove(obj);
	for (GameObject* o : objects)
	{
		if (o->isColliding())
		{
			Collider* collider = dynamic_cast<Collider*>(o);
			if (collider != NULL)
			{
				Rectangle colliderPos = collider->getCollisionPos(o);
				if (CheckCollisionRecs(collisonPos, colliderPos))
				{
					return true;
				}
					
			}
			
		}
			
	}
	return false;
}
