#pragma once
#include "Recipes.h"
#include "../Items/Item.h"
class CraftingStation
{
	CraftingStationEnum station;
	std::vector<Recipes*> allRecepies;
	std::vector<Recipes*> itemsICanCraft;
	int firstItem = 0;
	bool onlyICanCraft = true;
public:
	CraftingStation(CraftingStationEnum station);
	/// <summary>
	/// Aktualnia itemy które mo¿emy stworzyæ
	/// </summary>
	/// <param name="items">Itemy jakie posiadamy</param>
	void updateItemsICanCraft(std::vector<Item*> items);
	/// <summary>
	/// Tworzy item o podanym Id z itemów co mozemy stworzyæ
	/// </summary>
	/// <param name="items">Itemy jakie posiadamy</param>
	/// <returns>Item stworzony</returns>
	Item* craftItem(std::vector<Item*> items);
	void goToPrevisItem();
	void goToNextItem();
	void changeItemsSee(bool itemsOnlyIcanCraft);
	void swapItemsSee();
	void draw();
};

