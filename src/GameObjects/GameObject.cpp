#include "GameObject.h"
#include "../core/Scenes/GameScene.h"
#include "ItemFactory.h"
#include "PlantsFactory.h"
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
	case ObjectType::Plant:
		return Plants->getObject(ID);
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
	pos.x = j["Pos"][0];
	pos.y = j["Pos"][1];
	pos.width = j["Pos"][2];
	pos.height = j["Pos"][3];
	name = j["Name"];	
}

GameObject::GameObject(nlohmann::json &j, int ID)
{
	this->ID = ID;
	pos.x = j[ID]["Pos"][0];
	pos.y = j[ID]["Pos"][1];
	pos.width = j[ID]["Pos"][2];
	pos.height = j[ID]["Pos"][3];
	name = j[ID]["Name"];
	this->name[0] = std::toupper(this->name[0]);
}

GameObject::GameObject(std::string chunk, std::string objDataPlace, nlohmann::json &j)
{
	pos.x = j[chunk][objDataPlace]["Pos"][0];
	pos.y = j[chunk][objDataPlace]["Pos"][1];
	pos.width = j[chunk][objDataPlace]["Pos"][2];
	pos.height = j[chunk][objDataPlace]["Pos"][3];
	name = j[chunk][objDataPlace]["Name"];
	ID = j[chunk][objDataPlace]["ID"];
}
GameObject::~GameObject()
{

}

void GameObject::saveToJson(std::string chunk, std::string objDataPlace, nlohmann::json &j)
{
	j[chunk][objDataPlace]["Pos"][0] = (int)pos.x;
	j[chunk][objDataPlace]["Pos"][1] = (int)pos.y;
	j[chunk][objDataPlace]["Pos"][2] = (int)pos.width;
	j[chunk][objDataPlace]["Pos"][3] = (int)pos.height;
	j[chunk][objDataPlace]["Name"] = name;
	j[chunk][objDataPlace]["ID"] = ID;
	j[chunk][objDataPlace]["ObjType"] = getType();
	j[chunk][objDataPlace]["ObjClass"] = getType();
}

void GameObject::saveToJson(nlohmann::json &j)
{
	j["Pos"][0] = (int)pos.x;
	j["Pos"][1] = (int)pos.y;
	j["Pos"][2] = (int)pos.width;
	j["Pos"][3] = (int)pos.height;
	j["Name"] = name;
}
void GameObject::readFromJson(std::string chunk, std::string objDataPlace, nlohmann::json& j)
{
	pos.x = j[chunk][objDataPlace]["Pos"][0];
	pos.y = j[chunk][objDataPlace]["Pos"][1];
	pos.width = j[chunk][objDataPlace]["Pos"][2];
	pos.height = j[chunk][objDataPlace]["Pos"][3];
	name = j[chunk][objDataPlace]["Name"];
	ID = j[chunk][objDataPlace]["ID"];
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