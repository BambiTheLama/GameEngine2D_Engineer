#include "CraftingStation.h"
#include "../ItemFactory.h"
#include "../RecipesFactory.h"

CraftingStation::CraftingStation(CraftingStationEnum station)
{
	this->station = station;
	allRecepies = CraftingRecipes->getAllRecepies(station);
}

Item* CraftingStation::craftItem(Item*** items,int w,int h)
{
	if (onlyICanCraft)
	{
		if (itemsICanCraft.size() > 0)
			return itemsICanCraft[firstItem]->craftItem(items,w,h);
		else
			return NULL;
	}
	else
	{
		return allRecepies[firstItem]->craftItem(items,w,h);
	}
	
}

bool CraftingStation::checkItemsNeed(std::vector<ItemToRecipes> itemsToRec)
{

	int n = itemsToRec.size();
	for (ItemToRecipes r : itemsToRec)
	{
		for (Item* i : items)
		{
			if (i->getID() == r.itemID)
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
	this->items = items;
	itemsICanCraft.clear();
	for (Recipes* recepies : allRecepies)
	{
		std::vector<ItemToRecipes> itemsToRec = recepies->getItemsToBuild();
		if (checkItemsNeed(itemsToRec))
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
bool CraftingStation::isPressedCraft()
{
	if (!canSee)
		return false;
	Vector2 mouse = GetMousePosition();
	Rectangle pos = { 64,260,64,64 };
	if (CheckCollisionPointRec(mouse, pos))
	{
		return true;
	}
	for (int i = 1; i < 5; i++)
	{
		pos.x += pos.width * 5.0f / 4.0f;
		pos.width -= 8;
		pos.height -= 8;
		pos.y += 4;
		if (CheckCollisionPointRec(mouse, pos))
		{
			firstItem += i;
			if (onlyICanCraft)
			{
				firstItem %= itemsICanCraft.size();
			}
			else
			{
				firstItem %= allRecepies.size();
			}
			return false;
		}
		
	}
	return false;
}

bool hasID(int ID, std::vector<Recipes*> recepies)
{
	for (Recipes* r : recepies)
		if (r->getFinalItemID() == ID)
			return true;
	return false;
}
void CraftingStation::draw()
{
	if (!canSee)
		return;
	Rectangle pos = { 64,260,64,64 };
	Vector2 mouse = GetMousePosition();
	
	for (int i = 0; i < 5; i++)
	{
		///SZUKANIE ID ITEMU I RYSOWANIE KWADRATU
		int itemID = 0;
		Recipes* recepy;
		if (onlyICanCraft)
		{
			if (itemsICanCraft.size() > 0)
			{
				recepy = itemsICanCraft[(firstItem + i) % itemsICanCraft.size()];
			}
			else
				return;
			DrawRectangle(pos.x - 2, pos.y - 2, pos.width + 4, pos.height + 4, GREEN);
		}
		else
		{
			recepy = allRecepies[(firstItem + i) % allRecepies.size()];
			DrawRectangle(pos.x - 2, pos.y - 2, pos.width + 4, pos.height + 4, hasID(itemID, itemsICanCraft) ? GREEN : RED);
		}
		itemID = recepy->getFinalItemID();
		///RYSOWANIE PRZEDMIOTU
		DrawRectangleLinesEx({ pos.x - 2, pos.y - 2, pos.width + 4, pos.height + 4 }, 2, BLACK);
		Items->drawObjectAt(itemID, pos);

		///OPIS ITEMU
		if (CheckCollisionPointRec(mouse, pos))
		{

			std::string description = Items->getDescription(itemID);
			Vector2 descriptionSize = textSize(description.c_str(), 16);
			Rectangle dest = { mouse.x, mouse.y, descriptionSize.x, descriptionSize.y };
			DrawRectangleRounded(dest, 2, 2, BLUE);
			DrawText(description.c_str(), mouse.x, mouse.y, 16, BLACK);
			std::vector<ItemToRecipes> getItemsToBuild=recepy->getItemsToBuild();
			for (int j = 0; j < getItemsToBuild.size();j++)
			{
				Rectangle drawItem = { mouse.x + j * 40, mouse.y + descriptionSize.y, 32, 32 };
				DrawRectangleRec(drawItem, GREEN);
				Items->drawObjectAt(getItemsToBuild[j].itemID, drawItem);
				drawText(TextFormat("%d", getItemsToBuild[j].howMany), drawItem.x, drawItem.y, 16, BLACK);

			}
		}



		///OBLICZANIE POZYCJI KOLEJNEGO KWADRATU
		pos.x += pos.width * 5.0f / 4.0f;
		pos.width -= 8;
		pos.height -= 8;
		pos.y += 4;
	}
}