#include "Factory.h"

std::list<Factory*> Factory::factories;

void Factory::removeFactory(Factory* factory)
{
	factories.remove(factory);
}
void Factory::deleteAllFactory()
{
	std::list<Factory*> factories = Factory::factories;
	for (auto f : factories)
	{
		delete f;
	}
}
Factory::Factory()
{
	factories.push_back(this);
}

Factory::~Factory()
{
	removeFactory(this);
}