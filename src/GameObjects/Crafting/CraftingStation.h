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
	Rectangle pos[9];
public:
	CraftingStation(CraftingStationEnum station);
	/// <summary>
	/// Aktualnia itemy które mo¿emy stworzyæ
	/// </summary>
	/// <param name="items">Itemy jakie posiadamy</param>
	void updateItemsICanCraft(std::vector<Item*> items);
	/// <summary>
	/// Craftuje przedmiot wybrany na g³ównej pozycji 
	/// </summary>
	/// <param name="items">tablica 2 wymiarowa itemów do craftingu</param>
	/// <param name="w">szerokoœæ tablicy</param>
	/// <param name="h">Wysokoœæ tablicy</param>
	/// <returns>Stworzony item</returns>
	Item* craftItem(Item*** items, int w, int h);
	/// <summary>
	/// Sprawdz itemy potrzebne
	/// </summary>
	bool checkItemsNeed(std::vector<ItemToRecipes> itemsToRec);
	/// <summary>
	/// Zmienia czy widzimy itemy co mo¿emy tylko stworzyæ lub wszystkie dostêpne w danym miejscu
	/// </summary>
	/// <param name="itemsOnlyIcanCraft">Czy tylko itemy jakie widzimy</param>
	void changeItemsSee(bool itemsOnlyIcanCraft);
	/// <summary>
	/// Zmienia na itemy wszystkie widoczne lub tylko te co widzimy w zale¿noœci od poprzedniego stanu
	/// </summary>
	void swapItemsSee();
	/// <summary>
	/// Czy klikniêto craftowanie
	/// </summary>
	bool isPressedCraft();
	/// <summary>
	/// Rysuje crafting
	/// </summary>
	void draw();
	/// <summary>
	/// Swapuje czy widzimy crafting
	/// </summary>
	void swapVisibility() { canSee = !canSee; }
	/// <summary>
	/// Zwraca ID przedmiotu w zale¿noœci jaki crafting wybierzemy
	/// </summary>
	/// <param name="i">Numer receptury</param>
	int getItemID(int i);
	/// <summary>
	/// Zwraca Recepture przedmiotu w zale¿noœci jaki crafting wybierzemy
	/// </summary>
	/// <param name="i">Numer receptury</param>
	Recipes* getRecepies(int i);
	/// <summary>
	/// Zwraca czy item jaki tworzymy siê stakuje
	/// </summary>
	bool isStacableItem();
	/// <summary>
	/// Zwraca Id itemu craftowalnego
	/// </summary>
	int getItemID();
	/// <summary>
	/// Zwraca ile wykraftujemy tego przedmiotu
	/// </summary>
	int getStackSize();

	void goToPrevisItem();
	void goToNextItem();
};

