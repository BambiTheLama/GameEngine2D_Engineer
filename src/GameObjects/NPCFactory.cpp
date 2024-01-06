#include "NPCFactory.h"

#include "NPCFactory.h"

NPCFactory* NPCFactory::factory = NULL;

NPCFactory::NPCFactory()
{
	int i = 0;
	objects.push_back(new NPC({ 0,0,48,64 }, { 12,20,24,44 }, 200, "NPC1"));
	for (auto o : objects)
		o->ID = i++;
}
NPCFactory::~NPCFactory()
{
	factory = NULL;
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

NPC* NPCFactory::getObject(int ID)
{
	if (ID > -1 && ID < objects.size())
		return objects[ID]->clone();
	return NULL;
}
