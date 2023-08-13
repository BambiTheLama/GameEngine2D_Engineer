#pragma once
#include "../Items/Item.h"
#define EqWight 10
#define EqHeight 4
#define EqSize 48
#define EqSpacing 10
#define EqStartX 64
#define EqStartY 32
enum class sortBy {
	ID,NAME,Type
};
class Player;
/// <summary>
/// Klasa odpowiedzalna za ekwipunek gracza
/// </summary>
class Eq
{
	bool fullEq = false;
	int usingItem = 0, usingItemX = 0, usingItemY = 0;
	FaceSide faceSide;
	Item*** items = NULL;
	Player* player = NULL;
	Item* itemInHand = NULL;

public:
	/// <summary>
	/// Tworzy obiekt ekwipunku
	/// </summary>
	Eq(Player* player);
	/// <summary>
	/// Destruktor ekwipunku
	/// </summary>
	~Eq();
	/// <summary>
	/// Metoda od sortowania item�w
	/// </summary>
	/// <param name="typ">Po czym ma by� sortowane</param>
	void sortItems(sortBy typ);
	/// <summary>
	/// Metoda wykonuj�c uzycie przedmiotu kt�ry mamy aktualnie w r�ce
	/// </summary>
	/// <returns>Czy uda�o si� u�y� przedmiot</returns>
	bool useItem();
	/// <summary>
	/// Dodaje item do plecaka
	/// </summary>
	/// <param name="item">Item do dodania</param>
	/// <returns>Czy uda�o si� doda� item</returns>
	bool addItem(Item* item);
	/// <summary>
	/// Zwraca item w podanym przez nas slocie
	/// </summary>
	/// <param name="slotX">pozycja x</param>
	/// <param name="slotY">pozycja y</param>
	/// <returns>Item na podanej pozycji</returns>
	Item* getItem(int slotX, int slotY) { return items[slotY][slotX]; }
	/// <summary>
	/// Zwraca item u�ywany przez gracza
	/// </summary>
	/// <returns></returns>
	Item* getUsingItem() { return items[usingItemY][usingItemX]; }
	/// <summary>
	/// Aktualizuje pozycje itemu
	/// </summary>
	/// <param name="movePos">Pozycja do aktualizacji</param>
	void updateItemPos(Vector2 movePos);
	/// <summary>
	/// Metoda kt�ra aktualizuje ekwipunek
	/// </summary>
	void update();
	/// <summary>
	/// Aktualizuje u�ywany przedmiot na podstawie poruszenia k�kiem od myszy
	/// </summary>
	void mouseWeel();
	/// <summary>
	/// Sprawdza czy klikneli�my na eq
	/// </summary>
	bool isPressedOnEq();
	/// <summary>
	/// Aktualizuje pozycjie przedmiot�w je�li klikneli�my na eq
	/// </summary>
	void updateEqPressed();
	/// <summary>
	/// Metoda od rysowania ekwipunku
	/// </summary>
	void draw();
	/// <summary>
	/// Metoda rysuj�ca nasz przedmiot w r�ce
	/// </summary>
	void drawItem();
	/// <summary>
	/// Zmienia wstan eq na przeciwny
	/// </summary>
	void swapEqLook() { fullEq = !fullEq; }
	/// <summary>
	/// Ustawia w jak� strone jeste�my zwr�ceni
	/// </summary>
	/// <param name="side">strona w kt�r� jeste�my zwr�ceni</param>
	void setFaceSide(FaceSide side) { faceSide = side; }
	/// <summary>
	/// Zwraca wszystkie itemy jakie mamy w EQ
	/// </summary>
	/// <returns></returns>
	std::vector<Item*> getItems();
	/// <summary>
	/// Zwraca wszystkie przedmioty
	/// </summary>
	/// <returns></returns>
	Item*** getAllItems() { return items; }
	/// <summary>
	/// Sprawdza czy mo�emy dodac przedmiot do "R�ki"
	/// </summary>
	/// <param name="stacable">Czy przemiot si� stakuje</param>
	/// <param name="ID">ID przedmiotu</param>
	/// <param name="stackSize">Ile wynosi stak przedmiotu</param>
	/// <returns>Czy uda si� doda� do r�ki</returns>
	bool canAddItemToHand(bool stacable=false,int ID=0,int stackSize=0);
	/// <summary>
	/// Dodaje przemiot do r�ki
	/// </summary>
	/// <param name="item">Item jaki dodajemy</param>
	void addItemToHand(Item* item);
	/// <summary>
	/// Sprawdza czy mamy wolne miejsce w eq
	/// </summary>
	/// <returns>czy jest wolne miejsce</returns>
	bool isFullEq();
	/// <summary>
	/// Sprawdza czy mo�emy zestakowa� dany przedmiot
	/// </summary>
	/// <param name="item">Item sprawdzany czy mo�na stakowa�</param>
	/// <returns>Czy uda si� zestakowa� item</returns>
	bool canTakeItem(Item* item);
	/// <summary>
	/// Powoduje upuszczenie przedmiotu
	/// </summary>
	void dropItemFromHand();
	/// <summary>
	/// Czy mo�na zmieni� item czyli np je�li u�ywamy sikiery nie mo�na zmieni� podczas uderzania
	/// </summary>
	/// <returns></returns>
	bool canChangeItem();

	void endUsingItem();

	void removeItem(Item *item);

	void changeItem();
};

