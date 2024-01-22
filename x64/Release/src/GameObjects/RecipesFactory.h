#pragma once
#include "Factory.h"
#include "Crafting/Recipes.h"

#define CraftingRecipes RecipesFactory::getFactory()
class RecipesFactory 
{
	std::vector<Recipes*> recipes;
	static RecipesFactory* recipesFactory;
	RecipesFactory();
	~RecipesFactory();
public:
	static RecipesFactory* getFactory();

	Recipes* getRecpes(int ID) const;

	std::vector<Recipes*> getAllRecepies(CraftingStationEnum craftingStation);

	friend class Engine;
	friend class GameScene;
};

