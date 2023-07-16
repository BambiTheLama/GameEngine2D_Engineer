#include "ItemFactory.h"
#include "Items/Item.h"
#include "Items/Weapon/ShootingWeapon.h"
#include "Items/BlockItem.h"
ItemFactory* ItemFactory::factory = NULL;

ItemFactory::ItemFactory()
{
	std::string path = "Resource/Items/";
	int blockStackSize = 100;
	objects = std::vector<Item*>();
	objects.push_back(new BlockItem({ 0,0,32,32 }, "Wood", path + "Wood.png", blockStackSize));
	objects.push_back(new BlockItem({ 0,0,32,32 }, "Plank", path + "Plank.png", blockStackSize));
	objects.push_back(new BlockItem({ 0,0,32,32 }, "Dirt", path + "Dirt.png", blockStackSize));
	objects.push_back(new BlockItem({ 0,0,32,32 }, "Sand", path + "Sand.png", blockStackSize));
	objects.push_back(new BlockItem({ 0,0,32,32 }, "Plank", path + "Stone.png", blockStackSize));

	objects.push_back(new ShootingWeapon({ 0,0,32,32 }, ""));
	
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->ID = i;
	}
}

ItemFactory::~ItemFactory()
{
	for (auto i:objects)
		delete i;
	objects.clear();
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

