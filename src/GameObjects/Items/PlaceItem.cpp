#include "PlaceItem.h"
#include "../../core/Scenes/GameScene.h"
#include "../StructuresFactory.h"
#include "../Structures/Wall.h"
PlaceItem::PlaceItem(PlaceItem& item):StackItem(item)
{
	this->structID = item.structID;
}
PlaceItem::PlaceItem(Rectangle pos, std::string name, int stackSize,int structID) :StackItem(pos,name,stackSize)
{
	this->structID = structID;
}

PlaceItem::PlaceItem(nlohmann::json j):StackItem(j)
{
	if (j.contains("spawnObjectID"))
		this->structID = j["spawnObjectID"];
}

PlaceItem::~PlaceItem()
{

}

bool PlaceItem::use(float deltaTime)
{
	Vector2 destPos = getWordMousePos();
	GameObject* o = Structures->getObject(structID);
	if (!o)
		return false;
	Collider* c = dynamic_cast<Collider*>(o);
	Rectangle objectPos = { destPos.x,destPos.y,(float)tileSize * 2,(float)tileSize * 2 };
	if (c)
		objectPos = { destPos.x,destPos.y,c->getCollisionPos().width,c->getCollisionPos().height };


	std::list<GameObject*> objects = Game->getObjects(objectPos, ObjectToGet::getAll);
	if (objects.size() <= 0)
	{
		delete o;
		return false;
	}
	bool hasFloor = false;
	for (auto o : objects)
	{
		if (o->getType() == ObjectType::Block)
		{
			if (!CheckCollisionRecs(objectPos, o->getPos()))
				continue;
			if(o->getID() > 0)
				hasFloor = true;
			else
			{
				hasFloor = false;
				break;
			}

		}
		else
		{
			Collider* col = dynamic_cast<Collider*>(o);
			if (!col)
				continue;
			Rectangle rec = col->getCollisionPos();
			Rectangle objPos = o->getPos();
			rec.x += objPos.x;
			rec.y += objPos.y;
			if (CheckCollisionRecs(rec, objectPos))
			{
				hasFloor = false;
				break;
			}

		}
	}
	if (!hasFloor)
	{
		delete o;
		return false;
	}


	stackSize--;
	o->setMovePos(destPos);
	Game->addObject(o);


	return true;

}
void PlaceItem::drawInterface()
{
	Structures->drawInterface(structID, Game->worldToScreanPos(getWordMousePos()));
	
}
Vector2 PlaceItem::getWordMousePos()
{
	Vector2 cursorPos = Game->getCursorPos();
	Vector2 destPos;
	const int size = tileSize * 2;

	destPos.x = ((int)cursorPos.x) - (int)cursorPos.x % (size);
	if (cursorPos.x < 0)
		destPos.x -= size;
	destPos.y = ((int)cursorPos.y) - (int)cursorPos.y % (size);
	if (cursorPos.y < 0)
		destPos.y -= size;
	return destPos;
}