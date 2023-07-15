#include "ItemsDrop.h"


ItemsDrop::ItemsDrop()
{

}

ItemsDrop::ItemsDrop(ItemsDrop& itemsDrop)
{
	for (auto i : itemsDrop.items)
	{
		DropItem drop;
		drop.ID = i.ID;
		drop.dropChanse = i.dropChanse;
		drop.max = i.max;
		drop.min = i.min;
		items.push_back(drop);
	}
}

void ItemsDrop::addItemToDrop(int ID, float chanse, int max, int min)
{
	DropItem drop;
	drop.ID = ID;
	drop.dropChanse = chanse;
	drop.max = max;
	drop.min = min;
	items.push_back(drop);
}

std::vector<Item*> ItemsDrop::getDropFromEnemy()
{
	std::vector<Item*> itemsToReturn;

	for (DropItem i : items)
	{
		if (!i.wasDroped())
			continue;
		int n = i.howMuch()-1;
		Item* item = Items->getObject(i.ID);
		itemsToReturn.push_back(item);
		if (n > 1 && item->isStacable())
		{
			while (n > 0)
			{
				item->addToStack(n);
				if (item->getStackMaxSize() > n)
				{
					n -= item->getStackMaxSize();
					item = Items->getObject(i.ID);
					itemsToReturn.push_back(item);
				}
				else
					n = 0;
			}

		}
		else if(n > 1)
		{
			for (int k = 1; k < n; k++)
			{
				Item* item = Items->getObject(i.ID);
				itemsToReturn.push_back(item);
			}

		}
		
			
	}

	return itemsToReturn;
}
