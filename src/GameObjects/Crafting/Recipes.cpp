#include "Recipes.h"
#include "../ItemFactory.h"


Recipes::Recipes(int finalItemID,CraftingStationEnum whereToCraft)
{
	this->finalItemID = finalItemID;
	this->whereToCraft = whereToCraft;
}

void Recipes::addItemToRecipes(int ID, int howMany)
{
	ItemToRecipes items;
	items.ItemID = ID;
	items.howMany = howMany;
	itemsToBuildItem.push_back(items);
}

Item* Recipes::craftItem(Item*** items,int w,int h)
{
	return NULL;
}