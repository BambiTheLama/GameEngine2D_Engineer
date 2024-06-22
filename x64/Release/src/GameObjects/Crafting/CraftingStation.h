#pragma once
#include "Recipes.h"
#include "../Items/Item.h"


class CraftingStation
{
	bool onlyICanCraft = true;
	bool canSee = false;
	int firstItem = 0;
	Rectangle pos[9];
	std::vector<Item*> items;
	CraftingStationEnum station;
	std::vector<Recipes*> allRecepies;
	std::vector<Recipes*> itemsICanCraft;


public:
	CraftingStation(CraftingStationEnum station);
	/// <summary>
	/// Aktualnia itemy kt�re mo�emy stworzy�
	/// </summary>
	/// <param name="items">Itemy jakie posiadamy</param>
	void updateItemsICanCraft(std::vector<Item*> items);
	/// <summary>
	/// Craftuje przedmiot wybrany na g��wnej pozycji 
	/// </summary>
	/// <param name="items">tablica 2 wymiarowa item�w do craftingu</param>
	/// <param name="w">szeroko�� tablicy</param>
	/// <param name="h">Wysoko�� tablicy</param>
	/// <returns>Stworzony item</returns>
	Item* craftItem(Item*** items, int w, int h);
	/// <summary>
	/// Sprawdz itemy potrzebne
	/// </summary>
	bool checkItemsNeed(Recipes* recepies);
	/// <summary>
	/// Zmienia czy widzimy itemy co mo�emy tylko stworzy� lub wszystkie dost�pne w danym miejscu
	/// </summary>
	/// <param name="itemsOnlyIcanCraft">Czy tylko itemy jakie widzimy</param>
	void changeItemsSee(bool itemsOnlyIcanCraft);
	/// <summary>
	/// Zmienia na itemy wszystkie widoczne lub tylko te co widzimy w zale�no�ci od poprzedniego stanu
	/// </summary>
	void swapItemsSee();
	/// <summary>
	/// Czy klikni�to craftowanie
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

	void setVisibility(bool visible) { canSee = visible; }
	/// <summary>
	/// Zwraca ID przedmiotu w zale�no�ci jaki crafting wybierzemy
	/// </summary>
	/// <param name="i">Numer receptury</param>
	int getItemID(int i);
	/// <summary>
	/// Zwraca Recepture przedmiotu w zale�no�ci jaki crafting wybierzemy
	/// </summary>
	/// <param name="i">Numer receptury</param>
	Recipes* getRecepies(int i);
	/// <summary>
	/// Zwraca czy item jaki tworzymy si� stakuje
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
	/// <summary>
	/// Sprawdza czy zosta� klikni�ty panel tworzenia item�w
	/// </summary>
	/// <returns>Czy klikneli�my panel tworzenia item�w</returns>
	bool isPressedInCraftingUI();

	void goToPrevisItem();
	void goToNextItem();
};
