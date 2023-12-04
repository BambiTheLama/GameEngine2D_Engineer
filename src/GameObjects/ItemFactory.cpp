#include "ItemFactory.h"
#include "Items/Item.h"
#include "Items/StackItem.h"
#include "Items/Tool/ToolItem.h"
#include "Items/Weapon/Ammo.h"
#include "Items/Weapon/Bow.h"
#include "../core/Scenes/ItemEdytorStruct/ItemProperty.h"
#include <fstream>
#include "Items/PlaceItem.h"
ItemFactory* ItemFactory::factory = NULL;

ItemFactory::ItemFactory()
{
	
	nlohmann::json j;
	std::ifstream reader;
	reader.open("Items.json");
	if (reader.is_open())
		reader >> j;
	reader.close();
	for (int i = 0; i < j.size(); i++)
	{
		nlohmann::json itemRead = j[i];
		ItemClass type = (ItemClass)itemRead["ItemClass"];
		switch (type)
		{
		case ItemClass::StackItem:
			objects.push_back(new StackItem(itemRead));
			break;
		case ItemClass::ToolItem:
			objects.push_back(new ToolItem(itemRead));
			break;
		case ItemClass::Bow:
			objects.push_back(new Bow(itemRead));
			break;
		case ItemClass::Ammo:
			objects.push_back(new Ammo(itemRead));
			break;
		case ItemClass::PlaceItems:
			objects.push_back(new PlaceItem(itemRead));
			break;
		default:
			objects.push_back(new Item(itemRead));
			break;
		}
	}
	for (int i = 0; i < objects.size(); i++)
		objects[i]->ID = i;
	loadLanguage("PL");
	printf("[FactoryItem]: Stworzono fabryke itemow\n");
}

ItemFactory::~ItemFactory()
{
	for (auto i:objects)
		delete i;
	factory = NULL;
	objects.clear();
	printf("[FactoryItem]: Usunieto fabryke itemow\n");
}
void ItemFactory::clearFactory()
{
	if (factory)
	{
		delete factory;
	}

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

std::string ItemFactory::getDescription(int ID)
{ 
	if (ID < 0 || ID >= objects.size())
		return "";
	return objects[ID]->getDesctription(); 
}

void ItemFactory::drawItemDescription(int ID, int x, int y)
{
	if (ID < 0 || ID >= objects.size())
		return;
	objects[ID]->drawDescription(x,y);
}

Vector2 ItemFactory::itemDescriptionSize(int ID)
{
	if (ID < 0 || ID >= objects.size())
		return {0,0};
	return objects[ID]->getItemDescriptionSize();
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
	std::cout << j.dump(2) << std::endl;
	if(j.contains("ToolItem"))
		ToolItem::description = j["ToolItem"];
	if (j.contains("StackItem"))
		StackItem::description = j["StackItem"];
	if (j.contains("Bow"))
		Bow::description = j["Bow"];
	if (j.contains("Ammo"))
		Ammo::description = j["Ammo"];
	for (auto i : objects)
		i->loadLangue(j);

}
