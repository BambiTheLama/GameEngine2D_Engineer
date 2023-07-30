#pragma once
#include <vector> 
#include <list>
class Item;
/// <summary>
/// Definiuje w jakiej strukturze mo�na craftowa� przedmioty
/// </summary>
enum class CraftingStationEnum
{
	NON = 0 ,			//Dost�pne do craftowania wsz�dzie
	Workbanche = 1,		//Dost�pne do craftowania tylko w podstawowym craftingu
	Anvil = 2,			//Dost�pne w kowadle
};
/// <summary>
/// Struktura m�wi�ca co jest potrzebne i jakiej ilo�ci
/// </summary>
struct ItemToRecipes {
	int ItemID, howMany;

};
/// <summary>
/// Classa o receptur
/// </summary>
class Recipes
{
	int finalItemID;
	CraftingStationEnum whereToCraft;
	std::vector<ItemToRecipes> itemsToBuildItem;
public:
	Recipes(int finalItemID, CraftingStationEnum whereToCraft = CraftingStationEnum::NON);
	/// <summary>
	/// Dodaje item potrzebny by wykraftowa� przedmiot
	/// </summary>
	void addItemToRecipes(int ID, int howMeny=1);
	/// <summary>
	/// Zwraca ID itemu kt�ry craftujemy
	/// </summary>
	int getFinalItemID() { return finalItemID; }
	/// <summary>
	/// Zwraca gdzie mo�na wykona� przedmiot
	/// </summary>
	CraftingStationEnum getCraftingStation() { return whereToCraft; }
	/// <summary>
	/// Zwraca vektor potrzebnych przedmiot�w do wykonania przedmiotu
	/// </summary>
	std::vector<ItemToRecipes> getItemsToBuild()const { return itemsToBuildItem; }
	/// <summary>
	/// Craftuje przedmiot
	/// </summary>
	Item* craftItem(Item*** items, int w, int h);

};

