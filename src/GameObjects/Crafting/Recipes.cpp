#include "Recipes.h"
#include "../ItemFactory.h"
std::string getCraftingStationDescription()
{
	std::string s;
	s += "Dont need Station (" + std::to_string((int)(CraftingStationEnum::NON)) + ")";
	s += "\nNeed WorkBanche (" + std::to_string((int)(CraftingStationEnum::Workbanche)) + ")";
	s += "\nNeed Anvil (" + std::to_string((int)(CraftingStationEnum::Anvil)) + ")";
	return s;
}
Recipes::Recipes(nlohmann::json& j, int ID)
{
	if (j[ID].contains("finalItemID"))
		this->finalItemID = j[ID]["finalItemID"];
	else
		this->finalItemID = 0;

	if (j[ID].contains("whereToCraft"))
		this->whereToCraft = (CraftingStationEnum)j[ID]["whereToCraft"];
	else
		this->whereToCraft = CraftingStationEnum::NON;

	if (!Items->isStacableItem(finalItemID))
		howManyItems = 1;
	else if(j[ID].contains("howManyItems"))
		this->howManyItems = j[ID]["howManyItems"];
	else
		howManyItems = 1;
	std::string s = "Item";
	int i = 0;
	std::string tmp = s + std::to_string(i);
	while (j[ID].contains(tmp))
	{
		int Id = j[ID][tmp][0];
		int homMany = j[ID][tmp][1];
		addItemToRecipes(j[ID][tmp][0], j[ID][tmp][1]);
		i++;
		tmp = s + std::to_string(i);
	}
}

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
	{
		return NULL;
	}

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


			for (ItemToRecipes* recepy : itemsNeedToCraft)
			{
				if (recepy && items[y][x]->getID() == recepy->itemID && recepy->howMany > 0)
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
		if(i)
			delete i;
	Item* item = Items->getObject(finalItemID);

	item->setStackSize(howManyItems);

	return item;
}

void Recipes::saveToJson(nlohmann::json& j, int ID)
{

	j[ID]["finalItemID"] = finalItemID;
	j[ID]["whereToCraft"] = (int)whereToCraft;

	if (Items->isStacableItem(finalItemID))
		j[ID]["howManyItems"] = howManyItems;

	std::string s = "Item";
	std::string tmp;
	for (int i = 0; i < itemsToBuildItem.size(); i++)
	{
		tmp = s + std::to_string(i);
		j[ID][tmp][0] = itemsToBuildItem[i].itemID;
		j[ID][tmp][1] = itemsToBuildItem[i].howMany;
	}
}

void Recipes::copyItemData(Recipes& rec)
{
	finalItemID = rec.finalItemID;
	howManyItems = rec.howManyItems;
	whereToCraft = rec.whereToCraft;
	itemsToBuildItem.clear();
	for (ItemToRecipes i : rec.itemsToBuildItem)
	{
		ItemToRecipes item;
		item.itemID = i.itemID;
		item.howMany = i.howMany;
		itemsToBuildItem.push_back(item);
	}

	std::vector<ItemToRecipes> itemsToBuildItem;
}