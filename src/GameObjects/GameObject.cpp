#include "GameObject.h"
#include "../core/Scenes/GameScene.h"
#include "ItemFactory.h"
#include "StructuresFactory.h"
#include "BlockFactory.h"

GameObject* getObjFromFactory(ObjectType type, int ID)
{
	switch (type)
	{
	case ObjectType::NPC:
		break;
	case ObjectType::Item:
		return Items->getObject(ID);
	case ObjectType::Block:
		return Blocks->getObject(ID);
	case ObjectType::Particle:
		break;
	case ObjectType::Player:
		break;
	case ObjectType::NON:
		break;
	case ObjectType::Projectal:
		break;
	case ObjectType::Structure:
		return Structures->getObject(ID);
	default:
		break;
	}
	return NULL;
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
GameObject::GameObject(nlohmann::json& j)
{
	if (j.contains("Pos"))
	{
		pos.x = j["Pos"][0];
		pos.y = j["Pos"][1];
		pos.width = j["Pos"][2];
		pos.height = j["Pos"][3];
	}
	if (j.contains("Name"))
		name = j["Name"];	
	if(j.contains("ID"))
		ID = j["ID"];
}

GameObject::~GameObject()
{

}


void GameObject::saveToJson(nlohmann::json &j)
{
	j["Pos"][0] = (int)pos.x;
	j["Pos"][1] = (int)pos.y;
	j["Pos"][2] = (int)pos.width;
	j["Pos"][3] = (int)pos.height;
	j["Name"] = name;
	j["ID"] = ID;
	j["ObjType"] = getType();
	j["ObjClass"] = getType();
}
void GameObject::readFromJson(nlohmann::json& j)
{
	pos.x = j["Pos"][0];
	pos.y = j["Pos"][1];
	pos.width = j["Pos"][2];
	pos.height = j["Pos"][3];
	name = j["Name"];
	ID = j["ID"];
}
void GameObject::generateChunk()
{
	Rectangle pos = getPos();
	int x = pos.x + pos.width / 2;
	int w = tileSize * (ObjectHandler::w - 1);
	if (x >= 0)
		chunkX = x / w;
	else
		chunkX = (x - w) / w;
	int y = pos.y + pos.height / 2;
	int h = tileSize * (ObjectHandler::h - 1);
	if (y >= 0)
		chunkY = y / h;
	else
		chunkY = (y - h) / h;
}