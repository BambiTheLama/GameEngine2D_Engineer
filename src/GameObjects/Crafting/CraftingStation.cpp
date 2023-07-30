#include "CraftingStation.h"
#include "../ItemFactory.h"
#include "../RecipesFactory.h"

CraftingStation::CraftingStation(CraftingStationEnum station)
{
	this->station = station;
	allRecepies = CraftingRecipes->getAllRecepies(station);
}

Item* CraftingStation::craftItem(std::vector<Item*> items)
{
	return NULL;
}

bool checkItemsNeed(std::vector<ItemToRecipes> itemsToRec, std::vector<Item*> items)
{
	int n = itemsToRec.size();
	for (ItemToRecipes r : itemsToRec)
	{
		for (Item* i : items)
		{
			if (i->getID() == r.ItemID)
			{
				r.howMany -= i->getStackSize();
				if (r.howMany <= 0)
				{
					n--;
					break;
				}

			}
		}
	}


	return n <= 0;
}

void CraftingStation::updateItemsICanCraft(std::vector<Item*> items)
{
	itemsICanCraft.clear();
	for (Recipes* recepies : allRecepies)
	{
		std::vector<ItemToRecipes> itemsToRec = recepies->getItemsToBuild();
		if (checkItemsNeed(itemsToRec, items))
			itemsICanCraft.push_back(recepies);
	}
}

void CraftingStation::goToPrevisItem()
{
	firstItem--;
	if (firstItem < 0)
	{
		if (onlyICanCraft)
		{
			firstItem += itemsICanCraft.size();
		}
		else
		{
			firstItem += allRecepies.size();
		}
	}
}
void CraftingStation::goToNextItem()
{
	firstItem++;
	if (onlyICanCraft)
	{
		firstItem %= itemsICanCraft.size();
	}
	else
	{
		firstItem %= allRecepies.size();
	}
}
void CraftingStation::changeItemsSee(bool itemsOnlyIcanCraft) 
{ 
	onlyICanCraft = itemsOnlyIcanCraft; 
	firstItem = 0;
}
void CraftingStation::swapItemsSee()
{
	onlyICanCraft = !onlyICanCraft;
}
void CraftingStation::draw()
{
	Rectangle pos = { 64,260,64,64 };
	for (int i = 0; i < 5; i++)
	{
		int itemID = 0;
		if (onlyICanCraft)
		{
			if(itemsICanCraft.size()>0)
				itemID = itemsICanCraft[(firstItem + i) % itemsICanCraft.size()]->getFinalItemID();
		}
		else
		{
			itemID = allRecepies[(firstItem + i) % allRecepies.size()]->getFinalItemID();
		}
		DrawRectangle(pos.x - 2, pos.y - 2, pos.width + 4, pos.height + 4, GREEN);
		DrawRectangleLinesEx({ pos.x - 2, pos.y - 2, pos.width + 4, pos.height + 4 }, 2, BLACK);
		Items->drawObjectAt(itemID, pos);
		pos.x += pos.width * 5.0f / 4.0f;
		pos.width -= 8;
		pos.height -= 8;
		pos.y += 4;
	}
}