#include "ItemFactory.h"
#include "Items/Item.h"
#include "Items/StackItem.h"
#include "Items/Tool/ToolItem.h"
#include "Items/Weapon/Ammo.h"
#include "Items/Weapon/Bow.h"
#include "../core/Scenes/ItemEdytorStruct/ItemProperty.h"
#include <fstream>
ItemFactory* ItemFactory::factory = NULL;

ItemFactory::ItemFactory()
{
	loadLanguage("ENG");
	nlohmann::json j;
	std::ifstream reader;
	reader.open("Items.json");
	if (reader.is_open())
		reader >> j;
	reader.close();
	for (int i = 0; i < j.size(); i++)
	{
		ItemClass type = (ItemClass)j[i]["ItemClass"];
		switch (type)
		{
		case ItemClass::StackItem:
			objects.push_back(new StackItem(j, i));
			break;
		case ItemClass::ToolItem:
			objects.push_back(new ToolItem(j, i));
			break;
		case ItemClass::Bow:
			objects.push_back(new Bow(j, i));
			break;
		case ItemClass::Ammo:
			objects.push_back(new Ammo(j, i));
			break;
		default:
			objects.push_back(NULL);
			break;
		}
	}

	printf("[FactoryItem]: Stworzono fabryke itemow\n");
}

ItemFactory::~ItemFactory()
{
	for (auto i:objects)
		delete i;
	objects.clear();
	printf("[FactoryItem]: Usunieto fabryke itemow\n");
}
void ItemFactory::clearFactory()
{
	if (factory)
		delete factory;
}

ItemFactory* ItemFactory::getFactory()
{
	if (factory == NULL)
		factory = new ItemFactory();
	return factory;
}

Item* ItemFactory::getObject(int i) 
{
	if (i > -1 && i < objects.size())
		return objects[i]->clone();
	return NULL;
}

Item* ItemFactory::getObject(std::string name)
{
	for (auto* i : objects)
	{
		if (i->getName()._Equal(name))
			return i->clone();
	}
	return NULL;
}

void ItemFactory::drawObjectAt(int ID, Rectangle pos)
{
	if (ID < 0 || ID >= objects.size())
		return;
	if(objects[ID])
		objects[ID]->drawAt(pos);
}

void ItemFactory::drawItemDescription(int ID, int x, int y)
{
	if (ID < 0 || ID >= objects.size())
		return;
	std::string description = getDescription(ID);
	Vector2 descriptionSize = textSize(description.c_str(), textStandardSize);
	Rectangle dest = { x, y, descriptionSize.x, descriptionSize.y };
	DrawRectangleRec(dest, BLUE);
	drawText(description.c_str(), x, y, textStandardSize, BLACK);
}

bool ItemFactory::isStacableItem(int ID)
{
	if (ID < 0 || ID >= objects.size())
		return false;
	if (objects[ID])
		return objects[ID]->isStacable();
	return false;
}
void ItemFactory::loadLanguage(std::string language)
{
	nlohmann::json j;
	std::ifstream reader;
	reader.open(language+".json");
	if (!reader.is_open())
		return;
	reader >> j;
	reader.close();
	ToolItem::description = j["ToolItem"]["DES"];
	StackItem::description = j["StackItem"]["DES"];
	Bow::description = j["Bow"]["DES"];
	Ammo::description = j["Ammo"]["DES"];
}
