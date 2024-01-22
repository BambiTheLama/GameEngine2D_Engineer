#include "RecipesFactory.h"
#include <fstream>
#include "json.hpp"

RecipesFactory* RecipesFactory::recipesFactory = NULL;

RecipesFactory::RecipesFactory()
{
	recipesFactory = this;
	nlohmann::json j;
	std::ifstream reader;
	reader.open("Resource/Recepies.json");
	if (reader.is_open())
	{
		reader >> j;

	}
	reader.close();
	for (int i = 0; i < j.size(); i++)
	{
		recipes.push_back(new Recipes(j, i));
	}
}

RecipesFactory::~RecipesFactory()
{
	recipesFactory = NULL;
	for (auto r : recipes)
		delete r;
	recipes.clear();
}

RecipesFactory* RecipesFactory::getFactory()
{
	if (recipesFactory == NULL)
		recipesFactory = new RecipesFactory();
	return recipesFactory;
}

Recipes* RecipesFactory::getRecpes(int ID) const
{
	if (ID < 0 || ID >= recipes.size())
		return NULL;
	return recipes[ID];

}

std::vector<Recipes*> RecipesFactory::getAllRecepies(CraftingStationEnum craftingStation)
{
	std::vector<Recipes*> objs;
	for(Recipes* re:recipes)
		if (re->getCraftingStation() == craftingStation)
		{
			objs.push_back(re);
		}
	return objs;
}
