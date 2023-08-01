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
/// <summary>
/// Klasa odpowiedzalna za ekwipunek gracza
/// </summary>
class Eq
{
	int usingItem = 0, usingItemX = 0, usingItemY = 0;
	Item*** items = NULL;
	bool fullEq=false;
	FaceSide faceSide;
public:
	/// <summary>
	/// Tworzy obiekt ekwipunku
	/// </summary>
	Eq();
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
	/// Aktualizuje u¿ywany item na podstawie klikniêcia myszy
	/// </summary>
	void pressOnEq();
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

	void setFaceSide(FaceSide side) { faceSide = side; }
	/// <summary>
	/// Zwraca wszystkie itemy jakie mamy w EQ
	/// </summary>
	/// <returns></returns>
	std::vector<Item*> getItems();
	Item*** getAllItems() { return items; }
};

