#include "StructuresFactory.h"
#include "Structures/Tree.h"
#include "Structures/Rock.h"
#include "Structures/Wall.h"
StructuresFactory* StructuresFactory::structuresFactory = NULL;

StructuresFactory::StructuresFactory()
{
	objects.push_back(new Tree({ 0, 0, 128, 128 }, "Tree", 0, 0));
	objects.push_back(new Structure({ 0, 0, 32, 32 }, "Clover"));
	objects.push_back(new Rock({ 0, 0, 64, 64 }, "Rock", 3));
	objects.push_back(new Wall({ 0,0,64,64 }, "WoodWall", ToolType::Axe, 5, 10));
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->ID = i;
	}
	printf("[StructuresFactory]: Dodano fabryke struktor\n");
}

StructuresFactory::~StructuresFactory()
{
	for (auto* o : objects)
		delete o;
	objects.clear();
	printf("[StructuresFactory]: Usunieto fabryke struktor\n");
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
