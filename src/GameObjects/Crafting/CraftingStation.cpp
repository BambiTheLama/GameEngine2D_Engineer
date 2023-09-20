#include "CraftingStation.h"
#include "../ItemFactory.h"
#include "../RecipesFactory.h"

CraftingStation::CraftingStation(CraftingStationEnum station)
{
	this->station = station;
	allRecepies = CraftingRecipes->getAllRecepies(station);
	pos[4] = {300,260,64,64};
	for (int i = 1; i < 5; i++)
	{
		pos[4 + i] = { pos[4 + i - 1].x + pos[4 + i - 1].width * 5.0f / 4.0f ,
			pos[4 + i - 1].y + 4,
			pos[4 + i - 1].width - 8,
			pos[4 + i - 1].height - 8
		};

		pos[4 - i] = { pos[4 + 1 - i].x,
			pos[4 - i + 1].y + 4,
			pos[4 - i + 1].width - 8,
			pos[4 - i + 1].height - 8
		};
		pos[4 - i].x -= pos[4 - i].width * 5.0f / 4.0f;
	}
}

Item* CraftingStation::craftItem(Item*** items,int w,int h)
{
	if (onlyICanCraft)
	{
		if (itemsICanCraft.size() > 0 && firstItem< itemsICanCraft.size())
		{
			return itemsICanCraft[firstItem]->craftItem(items, w, h);
		}
		else
			return NULL;
	}
	else
	{
		return allRecepies[firstItem]->craftItem(items,w,h);
	}
	return NULL;
}

bool CraftingStation::checkItemsNeed(Recipes* recepies)
{
	std::vector<ItemToRecipes> itemsToRec = recepies->getItemsToBuild();
	int n = itemsToRec.size();
	for (int i=0;i<itemsToRec.size();i++)
	{
		ItemToRecipes r = itemsToRec[i];
		recepies->setItemStatus(i,CraftStatus::DontHave);
		for (Item* item : items)
		{
			if (item->getID() == r.itemID)
			{
				

				r.howMany -= item->getStackSize();
				if (r.howMany <= 0)
				{
					n--;
					recepies->setItemStatus(i, CraftStatus::Have);
					break;
				}
				else
				{
					recepies->setItemStatus(i, CraftStatus::NotEnough);
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
		if (checkItemsNeed(recepies))
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

	if (CheckCollisionPointRec(mouse, pos[4]))
	{
		if (itemsICanCraft.size() <= 0)
			return false;
		return true;
	}
	for (int i = 0; i < 4; i++)
	{
		if (CheckCollisionPointRec(mouse, pos[i]))
		{
			firstItem -= 4 - i;
			if (onlyICanCraft)
			{
				if (itemsICanCraft.size() > 0)
					firstItem = (firstItem + itemsICanCraft.size())%(itemsICanCraft.size());
			}
			else
			{
				if (allRecepies.size() > 0)
					firstItem = (firstItem + allRecepies.size()) % (allRecepies.size());
			}
			return false;
		}
		
	}
	for (int i = 1; i < 5; i++)
	{
		if (CheckCollisionPointRec(mouse, pos[4+i]))
		{
			firstItem += i;
			if (onlyICanCraft)
			{
				if (itemsICanCraft.size() > 0)
					firstItem %= itemsICanCraft.size();
			}
			else
			{
				if (allRecepies.size() > 0)
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
	Vector2 mouse = GetMousePosition();
	int firstItem = this->firstItem - 4;

	for (int i = 0; i < 9; i++)
	{
		Rectangle pos = this->pos[i];
		///SZUKANIE ID ITEMU I RYSOWANIE KWADRATU
		int itemID = getItemID(i + firstItem);
		///RYSOWANIE PRZEDMIOTU
		DrawRectangle(pos.x - 2, pos.y - 2, pos.width + 4, pos.height + 4, hasID(itemID, itemsICanCraft) ? GREEN : RED);
		DrawRectangleLinesEx({ pos.x - 2, pos.y - 2, pos.width + 4, pos.height + 4 }, 2, BLACK);
		Items->drawObjectAt(itemID, pos);

	}
	for (int i = 0; i < 9; i++)
	{
		Rectangle pos = this->pos[i];
		///OPIS ITEMU
		if (CheckCollisionPointRec(mouse, pos))
		{
			Vector2 starPoint = { pos.x +pos.width/2, pos.y + pos.width };
			int itemID = 0;
			Recipes* recepy = getRecepies(i + firstItem);
			if (recepy == NULL)
				return;
			itemID = recepy->getFinalItemID();
			std::string description = Items->getDescription(itemID);
			Vector2 descriptionSize = Items->itemDescriptionSize(itemID);
			starPoint.x -= descriptionSize.x / 2;
			Items->drawItemDescription(itemID, starPoint.x, starPoint.y);


			///Rysowanie itemów potrzebnych do stworzenia przedmiotu
			std::vector<ItemToRecipes> getItemsToBuild = recepy->getItemsToBuild();
			for (int j = 0; j < getItemsToBuild.size(); j++)
			{
				Rectangle drawItem = { starPoint.x + j * 32, starPoint.y + descriptionSize.y, 32, 32 };
				Color itemColor=GRAY;
				switch (getItemsToBuild[j].status)
				{
				case CraftStatus::DontHave:
					itemColor = RED;
					break;
				case CraftStatus::NotEnough:
					itemColor = YELLOW;
					break;
				case CraftStatus::Have:
					itemColor = GREEN;
					break;		
				}
				DrawRectangleRec(drawItem, itemColor);
				Items->drawObjectAt(getItemsToBuild[j].itemID, { drawItem.x + 4,drawItem.y + 4 ,20,20 });
				const char* text = TextFormat("%d", getItemsToBuild[j].howMany);

				Vector2 textSpace = textSize(text, textStandardSize2);
				Vector2 textPos = { drawItem.x + drawItem.width - textSpace.x, drawItem.y + drawItem.height - textSpace.y };
				drawText(text, textPos.x-2, textPos.y-2, textStandardSize2, BLACK);
				DrawRectangleLinesEx(drawItem, 2, BLACK);
			}
		}
	}

}

int CraftingStation::getItemID(int i)
{
	if (onlyICanCraft)
	{
		if (i < 0)
			i += itemsICanCraft.size() * 4;

		if (itemsICanCraft.size() > 0)
			return itemsICanCraft[(i) % itemsICanCraft.size()]->getFinalItemID();
	}
	else
	{
		if (i < 0)
			i += allRecepies.size() * 4;
		if (allRecepies.size() > 0)
			return allRecepies[(i) % allRecepies.size()]->getFinalItemID();
	}
	return 0;
}

Recipes* CraftingStation::getRecepies(int i)
{
	if (onlyICanCraft)
	{

		if (itemsICanCraft.size() > 0)
		{
			if (i < 0)
				return itemsICanCraft[(i + itemsICanCraft.size() * (-i)) % itemsICanCraft.size()];
			else
				return itemsICanCraft[(i) % itemsICanCraft.size()];

		}

		
	}
	else
	{

		if (allRecepies.size() > 0)
		{
			if (i < 0)
				return allRecepies[(i+(-i)* allRecepies.size()) % allRecepies.size()];
			else
				return allRecepies[(i) % allRecepies.size()];
		}
	}
	return NULL;
}

bool CraftingStation::isStacableItem()
{
	return Items->isStacableItem(getItemID());
}

int CraftingStation::getItemID()
{
	return getItemID(firstItem);
}

int CraftingStation::getStackSize()
{
	return getRecepies(firstItem)->getHowManyItems();
}

bool CraftingStation::isPressedInCraftingUI()
{
	Rectangle craftingPos;
	craftingPos.x = pos[0].x;
	craftingPos.width = pos[8].x + pos[8].width;
	craftingPos.y = pos[4].y;
	craftingPos.height = pos[4].height;
	Vector2 mouse = GetMousePosition();
	return CheckCollisionPointRec(mouse, craftingPos);
}