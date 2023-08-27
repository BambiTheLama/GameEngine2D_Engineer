#include "PlantsFactory.h"
#include "Plants/Tree.h"
PlantsFactory* PlantsFactory::plantFactory = NULL;

PlantsFactory::PlantsFactory()
{
	objects.push_back(new Tree({ 0, 0, 128, 128 }, "Tree"));
	objects.push_back(new Plant({ 0, 0, 32, 32 }, "Clover"));
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->ID = i;
	}
	printf("[FactoryPlant]: Dodano fabryke roslin\n");
}

PlantsFactory::~PlantsFactory()
{
	for (auto* o : objects)
		delete o;
	objects.clear();
	printf("[FactoryPlant]: Usunieto fabryke roslin\n");
}

PlantsFactory* PlantsFactory::getFactory()
{
	if (plantFactory == NULL)
		plantFactory = new PlantsFactory();
	return plantFactory;
}

void PlantsFactory::clearFactory()
{
	if (plantFactory)
		delete plantFactory;

}

Plant* PlantsFactory::getObject(int ID)
{
	if (ID < 0 || ID >= objects.size())
		return NULL;
	return objects[ID]->clone();
}