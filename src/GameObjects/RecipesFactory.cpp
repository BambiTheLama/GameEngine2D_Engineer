#include "RecipesFactory.h"

RecipesFactory* RecipesFactory::recipesFactory = NULL;

RecipesFactory::RecipesFactory()
{
	recipesFactory = this;
	Recipes *recepe=new Recipes(5);
	recepe->addItemToRecipes(0, 20);
	recepe->addItemToRecipes(1, 20);
	recipes.push_back(recepe);
	recepe = new Recipes(6);
	recepe->addItemToRecipes(0, 69);
	recipes.push_back(recepe);
	recepe = new Recipes(7);
	recepe->addItemToRecipes(0, 21);
	recipes.push_back(recepe);
	recepe = new Recipes(8);
	recepe->addItemToRecipes(0, 37);
	recipes.push_back(recepe);
	recepe = new Recipes(1,CraftingStationEnum::NON,4);
	recepe->addItemToRecipes(0, 1);
	recipes.push_back(recepe);
}

RecipesFactory::~RecipesFactory()
{
	recipesFactory = NULL;
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