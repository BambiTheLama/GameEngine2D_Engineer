#include "GameObject.h"
#include "../core/Scenes/GameScene.h"


GameObject::GameObject(GameObject& obj)
{
	this->pos = obj.pos;
	this->ID = obj.ID;
	this->name = obj.name;
}
GameObject::GameObject(Rectangle pos,std::string name)
{
	this->pos = pos;
	this->name = name;
	this->name[0] = std::toupper(this->name[0]);
}

GameObject::GameObject(nlohmann::json j, int ID)
{
	this->ID = ID;
	pos.x = j[ID]["Pos"][0];
	pos.y = j[ID]["Pos"][1];
	pos.width = j[ID]["Pos"][2];
	pos.height = j[ID]["Pos"][3];
	name = j[ID]["Name"];
	this->name[0] = std::toupper(this->name[0]);
}
GameObject::~GameObject()
{

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
bool isOnLine(float p1, float p2, float x)
{
	if (p1 > p2)
	{
		return x >= p2 && x <= p1;
	}
	else
	{
		return x >= p1 && x <= p2;
	}
}

bool checkCollision(Vector2 points[4], Rectangle pos)
{
	for (int i = 0; i < 4; i++)
	{

		Vector2 p1 = points[i];
		Vector2 p2 = points[(i + 1) % 4];
		int a = (p1.y - p2.y) / (p1.x - p2.x);
		int b = p1.y - a * p1.x;
		int x = (pos.y - b) / a;
		
		if (x >= pos.x && x <= pos.x + pos.width && isOnLine(p1.x, p2.x, x))
		{
			return true;
		}
		x = (pos.y + pos.height - b) / a;
		if (x >= pos.x && x <= pos.x + pos.width && isOnLine(p1.x, p2.x, x))
		{
			return true;
		}
		int y = pos.x * a + b;
		if (y >= pos.y && y <= pos.y + pos.height && isOnLine(p1.x, p2.x, pos.x))
		{
			return true;
		}
		y = (pos.x + pos.width) * a + b;
		if (y >= pos.y && y <= pos.y + pos.height && isOnLine(p1.x, p2.x, pos.x + pos.width))
		{
			return true;
		}

	}
	return false;
}

bool checkCollision(Vector2 points[4], Vector2 points2[4])
{
	for (int i = 0; i < 4; i++)
	{

		Vector2 p1 = points[i];
		Vector2 p2 = points[(i + 1) % 4];
		int a1 = (p1.y - p2.y) / (p1.x - p2.x);
		int b1 = p1.y - a1 * p1.x;
		for (int j = 0; j < 4; j++)
		{
			Vector2 p3 = points2[i];
			Vector2 p4 = points2[(i + 1) % 4];
			int a2 = (p3.y - p4.y) / (p3.x - p4.x);
			int b2 = p3.y - a2 * p3.x;
			int x = (b2 - b1) / (a1 - a2);
			if (isOnLine(p1.x, p2.x, x) && isOnLine(p3.x, p4.x, x))
				return true;
		}

	}
	return false;
}