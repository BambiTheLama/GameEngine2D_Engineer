#include "NPCFactory.h"

NPCFactory* NPCFactory::factory = NULL;

NPCFactory::NPCFactory()
{
	int i = 0;
	for (auto o : objects)
		o->ID = i++;
}
NPCFactory::~NPCFactory()
{
	for (auto o : objects)
		delete o;
	objects.clear();
}

NPCFactory* NPCFactory::getFactory()
{
	if (!factory)
		factory = new NPCFactory();
	return factory;
}

void NPCFactory::clearFactory()
{
	if (factory)
	{
		delete factory;
		factory = NULL;
	}

}

Enemy* NPCFactory::getObject(int ID)
{
	if (ID > -1 && ID < objects.size())
		return objects[ID]->clone();
	return NULL;
}
