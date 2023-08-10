#pragma once
#include <vector> 
#include <list>
class Item;
/// <summary>
/// Definiuje w jakiej strukturze mo¿na craftowaæ przedmioty
/// </summary>
enum class CraftingStationEnum
{
	NON = 0 ,			//Dostêpne do craftowania wszêdzie
	Workbanche = 1,		//Dostêpne do craftowania tylko w podstawowym craftingu
	Anvil = 2,			//Dostêpne w kowadle
};
/// <summary>
/// Definiuje czy posiadamy dany sk³adnik do scraftowania
/// </summary>
enum class CraftStatus
{
	DontHave,			//Nie Posiadasz tego itemu
	NotEnough,			//Posiadasz item ale nie wystarczaj¹ca iloœæ
	Have				//Posiadasz item i ile potrzebujesz 
};
/// <summary>
/// Struktura mówi¹ca co jest potrzebne i jakiej iloœci
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
	/// Dodaje item potrzebny by wykraftowaæ przedmiot
	/// </summary>
	void addItemToRecipes(int ID, int howMeny=1);
	/// <summary>
	/// Zwraca ID itemu który craftujemy
	/// </summary>
	int getFinalItemID() { return finalItemID; }
	/// <summary>
	/// Zwraca ile wykonamy przedmiotów
	/// </summary>
	/// <returns>iloœc przedmiotów</returns>
	int getHowManyItems() { return howManyItems; }
	/// <summary>
	/// Zwraca gdzie mo¿na wykonaæ przedmiot
	/// </summary>
	CraftingStationEnum getCraftingStation() { return whereToCraft; }
	/// <summary>
	/// Zwraca vektor potrzebnych przedmiotów do wykonania przedmiotu
	/// </summary>
	std::vector<ItemToRecipes> getItemsToBuild()const { return itemsToBuildItem; }
	void setItemStatus(int i, CraftStatus status) { itemsToBuildItem[i].status = status; }
	/// <summary>
	/// Craftuje przedmiot
	/// </summary>
	Item* craftItem(Item*** items, int w, int h);
	/// <summary>
	/// Sprawdza czy z podanych itemów mo¿na zrobiæ przedmiot
	/// </summary>
	/// <param name="items">Itemy z ekwipunku</param>
	/// <param name="w">szerokoœæ eq</param>
	/// <param name="h">wysokoœæ eq</param>
	/// <returns>Czy mo¿na zrobiæ przedmiot</returns>
	bool canCraft(Item*** items, int w, int h);

};

