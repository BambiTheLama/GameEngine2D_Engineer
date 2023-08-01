#pragma once
#include "Recipes.h"
#include "../Items/Item.h"


class CraftingStation
{
	CraftingStationEnum station;
	std::vector<Recipes*> allRecepies;
	std::vector<Recipes*> itemsICanCraft;
	std::vector<Item*> items;
	int firstItem = 0;
	bool onlyICanCraft = true;
	bool canSee = false;
public:
	CraftingStation(CraftingStationEnum station);
	/// <summary>
	/// Aktualnia itemy które mo¿emy stworzyæ
	/// </summary>
	/// <param name="items">Itemy jakie posiadamy</param>
	void updateItemsICanCraft(std::vector<Item*> items);

	Item* craftItem(Item*** items, int w, int h);
	bool checkItemsNeed(std::vector<ItemToRecipes> itemsToRec);
	void goToPrevisItem();
	void goToNextItem();
	void changeItemsSee(bool itemsOnlyIcanCraft);
	void swapItemsSee();
	bool isPressedCraft();
	void draw();
	void swapVisibility() { canSee = !canSee; }
};

