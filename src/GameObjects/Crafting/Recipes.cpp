#include "Recipes.h"
#include "../ItemFactory.h"


Recipes::Recipes(int finalItemID,CraftingStationEnum whereToCraft,int howManyItems)
{
	this->finalItemID = finalItemID;
	this->whereToCraft = whereToCraft;
	if (!Items->isStacableItem(finalItemID))
		howManyItems = 1;
	this->howManyItems = howManyItems;

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
	std::list<ItemToRecipes*> itemsNeedToCraft;
	for (ItemToRecipes i : itemsToBuildItem)
	{
		ItemToRecipes *tmp = new ItemToRecipes();
		tmp->howMany = i.howMany;
		tmp->itemID = i.itemID;
		itemsNeedToCraft.push_back(tmp);
	}
	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			if (items[y][x] == NULL)
				continue;


			for (ItemToRecipes *recepy : itemsNeedToCraft)
			{
				if (recepy != NULL && items[y][x]->getID() == recepy->itemID && recepy->howMany > 0)
				{
					if (items[y][x]->getStackSize() > recepy->howMany)
					{
						items[y][x]->removeFromStack(recepy->howMany);
						recepy->howMany = 0;

						break;
					}
					else
					{
						recepy->howMany -= items[y][x]->getStackSize();
						items[y][x]->removeFromStack(items[y][x]->getStackSize());
						delete items[y][x];
						items[y][x] = NULL;
						break;
					}

				}
			}
		
		}
	}
	for (ItemToRecipes *i : itemsNeedToCraft)
		if(i!=NULL)
			delete i;
	Item* item = Items->getObject(finalItemID);
	item->setStackSize(howManyItems);
	return item;
}