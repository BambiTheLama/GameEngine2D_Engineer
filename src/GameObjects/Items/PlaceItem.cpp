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

	std::list<GameObject*> objects = Game->getObjects({ cursorPos.x,cursorPos.y,(float)size,(float)size }, ObjectToGet::getAll);
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
			hasFloor = false;
			break;
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

	objects = Game->getObjects({ cursorPos.x - size * 1,cursorPos.y - size * 1,(float)size*3,(float)size*3 }, ObjectToGet::getNoBlocks);
	for (auto o : objects)
	{
		if (o->getType() != ObjectType::Structure)
			continue;
		Wall* w = dynamic_cast<Wall*>(o);
		if (!w)
			continue;
		w->generateTexturePos();
	}
	return true;

}
