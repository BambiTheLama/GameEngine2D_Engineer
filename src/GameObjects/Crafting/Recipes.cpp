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
	items.itemID = ID;
	items.howMany = howMany;
	itemsToBuildItem.push_back(items);
}
bool Recipes::canCraft(Item*** items, int w, int h)
{
	std::list<ItemToRecipes> itemsNeedToCraft;
	for (ItemToRecipes i : itemsToBuildItem)
	{
		itemsNeedToCraft.push_back(i);
	}
	int n = itemsNeedToCraft.size();
	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			if (items[y][x] == NULL)
				continue;
			for (ItemToRecipes recepy : itemsNeedToCraft)
			{
				if (items[y][x]->getID() == recepy.itemID)
				{
					recepy.howMany -= items[y][x]->getStackSize();
					if (recepy.howMany <= 0)
					{
						n--;
						if (n == 0)
							return true;
					}
				}
			}
		}
	}

	return false;
}
Item* Recipes::craftItem(Item*** items,int w,int h)
{
	if (!canCraft(items, w, h))
		return NULL;
	std::list<ItemToRecipes> itemsNeedToCraft;
	for (ItemToRecipes i : itemsToBuildItem)
	{
		itemsNeedToCraft.push_back(i);
	}
	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			if (items[y][x] == NULL)
				continue;


			for (ItemToRecipes recepy : itemsNeedToCraft)
			{
				if (items[y][x]->getID() == recepy.itemID && recepy.howMany > 0)
				{
					if (items[y][x]->getStackSize() > recepy.howMany)
					{
						items[y][x]->removeFromStack(recepy.howMany);
						recepy.howMany = 0;
						break;
					}
					else
					{
						recepy.howMany -= items[y][x]->getStackSize();
						items[y][x]->removeFromStack(items[y][x]->getStackSize());
						delete items[y][x];
						items[y][x] = NULL;
						break;
					}

				}
			}
		
		}
	}
	return Items->getObject(finalItemID);
}