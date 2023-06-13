#include "ItemFactory.h"
#include "Items/Item.h"
#include "Items/Weapon/ShootingWeapon.h"

ItemFactory* ItemFactory::factory = NULL;

ItemFactory::ItemFactory()
{
	objects = std::vector<Item*>();
	objects.push_back(new ShootingWeapon({0,0,64,64}));
	

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

