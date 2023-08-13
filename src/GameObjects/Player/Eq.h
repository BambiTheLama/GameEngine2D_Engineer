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
	/// Metoda od sortowania itemów
	/// </summary>
	/// <param name="typ">Po czym ma byæ sortowane</param>
	void sortItems(sortBy typ);
	/// <summary>
	/// Metoda wykonuj¹c uzycie przedmiotu który mamy aktualnie w rêce
	/// </summary>
	/// <returns>Czy uda³o siê u¿yæ przedmiot</returns>
	bool useItem();
	/// <summary>
	/// Dodaje item do plecaka
	/// </summary>
	/// <param name="item">Item do dodania</param>
	/// <returns>Czy uda³o siê dodaæ item</returns>
	bool addItem(Item* item);
	/// <summary>
	/// Zwraca item w podanym przez nas slocie
	/// </summary>
	/// <param name="slotX">pozycja x</param>
	/// <param name="slotY">pozycja y</param>
	/// <returns>Item na podanej pozycji</returns>
	Item* getItem(int slotX, int slotY) { return items[slotY][slotX]; }
	/// <summary>
	/// Zwraca item u¿ywany przez gracza
	/// </summary>
	/// <returns></returns>
	Item* getUsingItem() { return items[usingItemY][usingItemX]; }
	/// <summary>
	/// Aktualizuje pozycje itemu
	/// </summary>
	/// <param name="movePos">Pozycja do aktualizacji</param>
	void updateItemPos(Vector2 movePos);
	/// <summary>
	/// Metoda która aktualizuje ekwipunek
	/// </summary>
	void update();
	/// <summary>
	/// Aktualizuje u¿ywany przedmiot na podstawie poruszenia kó³kiem od myszy
	/// </summary>
	void mouseWeel();
	/// <summary>
	/// Sprawdza czy klikneliœmy na eq
	/// </summary>
	bool isPressedOnEq();
	/// <summary>
	/// Aktualizuje pozycjie przedmiotów jeœli klikneliœmy na eq
	/// </summary>
	void updateEqPressed();
	/// <summary>
	/// Metoda od rysowania ekwipunku
	/// </summary>
	void draw();
	/// <summary>
	/// Metoda rysuj¹ca nasz przedmiot w rêce
	/// </summary>
	void drawItem();
	/// <summary>
	/// Zmienia wstan eq na przeciwny
	/// </summary>
	void swapEqLook() { fullEq = !fullEq; }
	/// <summary>
	/// Ustawia w jak¹ strone jesteœmy zwróceni
	/// </summary>
	/// <param name="side">strona w któr¹ jesteœmy zwróceni</param>
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
	/// Sprawdza czy mo¿emy dodac przedmiot do "Rêki"
	/// </summary>
	/// <param name="stacable">Czy przemiot siê stakuje</param>
	/// <param name="ID">ID przedmiotu</param>
	/// <param name="stackSize">Ile wynosi stak przedmiotu</param>
	/// <returns>Czy uda siê dodaæ do rêki</returns>
	bool canAddItemToHand(bool stacable=false,int ID=0,int stackSize=0);
	/// <summary>
	/// Dodaje przemiot do rêki
	/// </summary>
	/// <param name="item">Item jaki dodajemy</param>
	void addItemToHand(Item* item);
	/// <summary>
	/// Sprawdza czy mamy wolne miejsce w eq
	/// </summary>
	/// <returns>czy jest wolne miejsce</returns>
	bool isFullEq();
	/// <summary>
	/// Sprawdza czy mo¿emy zestakowaæ dany przedmiot
	/// </summary>
	/// <param name="item">Item sprawdzany czy mo¿na stakowaæ</param>
	/// <returns>Czy uda siê zestakowaæ item</returns>
	bool canTakeItem(Item* item);
	/// <summary>
	/// Powoduje upuszczenie przedmiotu
	/// </summary>
	void dropItemFromHand();
	/// <summary>
	/// Czy mo¿na zmieniæ item czyli np jeœli u¿ywamy sikiery nie mo¿na zmieniæ podczas uderzania
	/// </summary>
	/// <returns></returns>
	bool canChangeItem();

	void endUsingItem();

	void removeItem(Item *item);

	void changeItem();
};

