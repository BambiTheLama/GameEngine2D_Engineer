#include "ItemsDrop.h"
#include "../GameObject.h"
#include "../ItemFactory.h"
#include "../StructuresFactory.h"
#include "../BlockFactory.h"

void ItemsDrop::copyDataFrom(ItemsDrop& drops)
{

	for (auto i : drops.items)
	{
		DropItem drop;
		drop.ID = i.ID;
		drop.dropChanse = i.dropChanse;
		drop.max = i.max;
		drop.min = i.min;
		items.push_back(drop);
	}
}

ItemsDrop::ItemsDrop()
{

}

ItemsDrop::ItemsDrop(ItemsDrop& itemsDrop)
{
	copyDataFrom(itemsDrop);
}

ItemsDrop::ItemsDrop(ObjectType type, int ID)
{
	ItemsDrop* drop = NULL;
	GameObject* obj = getObjFromFactory(type, ID);
	if (obj)
	{
		drop = dynamic_cast<ItemsDrop*>(obj);
		if (drop)
			copyDataFrom(*drop);
		delete obj;
	}

}

void ItemsDrop::addItemToDrop(int ID, float chanse, int min, int max)
{
	DropItem drop;
	drop.ID = ID;
	drop.dropChanse = chanse;
	drop.max = max;
	drop.min = min;
	items.push_back(drop);
}

std::vector<Item*> ItemsDrop::getDrop()
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
				int left = item->addToStack(n);
				if (left > 0)
				{
					if (left == n)
						break;
					item = Items->getObject(i.ID);
					itemsToReturn.push_back(item);
				}
				n = left;
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
