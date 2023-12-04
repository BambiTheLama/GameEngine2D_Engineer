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
	Vector2 cursorPos = Game->getCursorPos();
	int size = tileSize * 2;
	cursorPos.x = ((int)cursorPos.x) - (int)cursorPos.x % (size)-tileSize;
	cursorPos.y = ((int)cursorPos.y) - (int)cursorPos.y % (size);
	GameObject* o = Structures->getObject(structID);
	if (!o)
		return false;
	Rectangle objectPos = { cursorPos.x,cursorPos.y,(float)size,(float)size };
	std::list<GameObject*> objects = Game->getObjects(objectPos, ObjectToGet::getAll);
	if (objects.size() <= 0)
	{
		delete o;
		return false;
	}
	bool hasFloor = false;
	for (auto o : objects)
	{
		if (o->getType() == ObjectType::Block && o->getID() > 0)
		{
			hasFloor = true;

		}
		else
		{
			Collider* col = dynamic_cast<Collider*>(o);
			if (!col)
				continue;
			Rectangle rec = col->getMaxRectangle();
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
	o->setMovePos(cursorPos);
	Game->addObject(o);


	return true;

}
