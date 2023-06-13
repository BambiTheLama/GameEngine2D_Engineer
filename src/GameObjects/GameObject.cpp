#include "GameObject.h"
#include "../core/Scenes/GameScene.h"

GameObject::GameObject(GameObject& obj)
{
	this->pos = obj.pos;
}
GameObject::GameObject(Rectangle pos)
{
	this->pos = pos;
}

float cursorTarget(Vector2 objPos)
{
	Vector2 mouse = Game->getCursorPos();
	float x = mouse.x - objPos.x;
	float y = mouse.y - objPos.y;
	float degree = atan(y / x);
	degree *= 180.0f / PI;
	degree -= 90;
	if (x >= 0)
		degree += 180;
	return degree;
}

float degreeToRadius(float degree)
{
	return degree * PI / 180;
}

float radiusToDegree(float radius)
{
	return radius / PI * 180;
}

Vector2 deltaFromDegree(float degree,float speed)
{
	Vector2 delta = { speed,-speed };
	delta.x *= sin(degreeToRadius(degree));
	delta.y *= cos(degreeToRadius(degree));
	return delta;
}

bool checkCollision(GameObject* obj)
{
	std::list<GameObject*> objs = Game->getObjects(obj->getPos());
	objs.remove(obj);
	for (GameObject* o : objs)
		if (o->isColliding())
		{
			if(CheckCollisionRecs(o->getPos(),obj->getPos()))
				return true;
		}
			
	return false;
}
