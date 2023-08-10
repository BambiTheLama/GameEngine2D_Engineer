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
/// Definiuje czy posiadamy dany sk�adnik do scraftowania
/// </summary>
enum class CraftStatus
{
	DontHave,			//Nie Posiadasz tego itemu
	NotEnough,			//Posiadasz item ale nie wystarczaj�ca ilo��
	Have				//Posiadasz item i ile potrzebujesz 
};
/// <summary>
/// Struktura m�wi�ca co jest potrzebne i jakiej ilo�ci
/// </summary>
struct ItemToRecipes {
	int itemID, howMany;
	CraftStatus status=CraftStatus::DontHave;
};
/// <summary>
/// Classa o receptur
/// </summary>
class Recipes
{
	int finalItemID;
	int howManyItems;
	CraftingStationEnum whereToCraft;
	std::vector<ItemToRecipes> itemsToBuildItem;
public:
	Recipes(int finalItemID, CraftingStationEnum whereToCraft = CraftingStationEnum::NON, int howManyItems = 1);
	/// <summary>
	/// Dodaje item potrzebny by wykraftowa� przedmiot
	/// </summary>
	void addItemToRecipes(int ID, int howMeny=1);
	/// <summary>
	/// Zwraca ID itemu kt�ry craftujemy
	/// </summary>
	int getFinalItemID() { return finalItemID; }
	/// <summary>
	/// Zwraca ile wykonamy przedmiot�w
	/// </summary>
	/// <returns>ilo�c przedmiot�w</returns>
	int getHowManyItems() { return howManyItems; }
	/// <summary>
	/// Zwraca gdzie mo�na wykona� przedmiot
	/// </summary>
	CraftingStationEnum getCraftingStation() { return whereToCraft; }
	/// <summary>
	/// Zwraca vektor potrzebnych przedmiot�w do wykonania przedmiotu
	/// </summary>
	std::vector<ItemToRecipes> getItemsToBuild()const { return itemsToBuildItem; }
	void setItemStatus(int i, CraftStatus status) { itemsToBuildItem[i].status = status; }
	/// <summary>
	/// Craftuje przedmiot
	/// </summary>
	Item* craftItem(Item*** items, int w, int h);
	/// <summary>
	/// Sprawdza czy z podanych item�w mo�na zrobi� przedmiot
	/// </summary>
	/// <param name="items">Itemy z ekwipunku</param>
	/// <param name="w">szeroko�� eq</param>
	/// <param name="h">wysoko�� eq</param>
	/// <returns>Czy mo�na zrobi� przedmiot</returns>
	bool canCraft(Item*** items, int w, int h);

};

