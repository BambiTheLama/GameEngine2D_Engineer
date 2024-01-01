#include "EnemyFactory.h"

EnemyFactory* EnemyFactory::factory = NULL;

EnemyFactory::EnemyFactory()
{
	int i = 0;
	objects.push_back(new Enemy());
	for (auto o : objects)
		o->ID = i++;
}
EnemyFactory::~EnemyFactory()
{
	for (auto o : objects)
		delete o;
	objects.clear();
}

EnemyFactory* EnemyFactory::getFactory()
{
	if (!factory)
		factory = new EnemyFactory();
	return factory;
}

void EnemyFactory::clearFactory()
{
	if (factory)
	{
		delete factory;
		factory = NULL;
	}

}

Enemy* EnemyFactory::getObject(int ID)
{
	if (ID > -1 && ID < objects.size())
		return objects[ID]->clone();
	return NULL;
}
