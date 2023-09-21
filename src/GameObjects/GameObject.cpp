#include "GameObject.h"
#include "../core/Scenes/GameScene.h"

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

Vector2 deltaFromDegree(float degree, float speed)
{
	Vector2 delta = { speed,-speed };
	delta.x *= sin(degreeToRadius(degree));
	delta.y *= cos(degreeToRadius(degree));
	return delta;
}

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



