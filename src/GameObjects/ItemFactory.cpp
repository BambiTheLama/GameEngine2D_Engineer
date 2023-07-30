#include "ItemFactory.h"
#include "Items/Item.h"
#include "Items/Weapon/ShootingWeapon.h"
#include "Items/BlockItem.h"
#include "Items/Tool/ToolItem.h"
ItemFactory* ItemFactory::factory = NULL;

ItemFactory::ItemFactory()
{
	int blockStackSize = 100;
	objects = std::vector<Item*>();
	objects.push_back(new BlockItem({ 0,0,32,32 }, "Wood", blockStackSize));
	objects.push_back(new BlockItem({ 0,0,32,32 }, "Plank", blockStackSize));
	objects.push_back(new BlockItem({ 0,0,32,32 }, "Dirt", blockStackSize));
	objects.push_back(new BlockItem({ 0,0,32,32 }, "Sand", blockStackSize));
	objects.push_back(new BlockItem({ 0,0,32,32 }, "Stone", blockStackSize));
	objects.push_back(new ToolItem({ 0,0,32,32 }, "Axe",ToolType::Axe,30));
	objects.push_back(new ToolItem({ 0,0,32,32 }, "Pickaxe", ToolType::Pickaxe,30));
	objects.push_back(new ToolItem({ 0,0,32,32 }, "Shovel",ToolType::Shovel,30));
	objects.push_back(new ToolItem({ 0,0,32,32 }, "Hoe",ToolType::NON,30));
	objects.push_back(new ShootingWeapon({ 0,0,32,32 }, ""));
	
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->ID = i;
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
	if (factory != NULL)
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
	objects[ID]->drawAt(pos);
}