#include "StructuresFactory.h"
#include "Plants/Tree.h"
StructuresFactory* StructuresFactory::structuresFactory = NULL;

StructuresFactory::StructuresFactory()
{
	objects.push_back(new Tree({ 0, 0, 128, 128 }, "Tree"));
	objects.push_back(new Plant({ 0, 0, 32, 32 }, "Clover"));
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->ID = i;
	}
	printf("[FactoryPlant]: Dodano fabryke roslin\n");
}

StructuresFactory::~StructuresFactory()
{
	for (auto* o : objects)
		delete o;
	objects.clear();
	printf("[FactoryPlant]: Usunieto fabryke roslin\n");
}

StructuresFactory* StructuresFactory::getFactory()
{
	if (structuresFactory == NULL)
		structuresFactory = new StructuresFactory();
	return structuresFactory;
}

void StructuresFactory::clearFactory()
{
	if (structuresFactory)
		delete structuresFactory;

}

GameObject* StructuresFactory::getObject(int ID)
{
	if (ID < 0 || ID >= objects.size())
		return NULL;
	return objects[ID]->clone();
}
