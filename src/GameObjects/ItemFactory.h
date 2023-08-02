#pragma once
#include "Items/Item.h"
#include <vector>
#include "Factory.h"

#define Items ItemFactory::getFactory()
/// <summary>
/// Fabryka Itemów zwraca nam kopiê obiektu
/// </summary>
class ItemFactory :Factory
{
	std::vector<Item*> objects;
	static ItemFactory* factory;
	/// <summary>
	/// Konstruktor domyœlny
	/// </summary>
	ItemFactory();
	/// <summary>
	/// Destruktor
	/// </summary>
	~ItemFactory();
public:
	/// <summary>
	/// Zwraca fabrykê
	/// </summary>
	/// <returns></returns>
	static ItemFactory* getFactory();
	/// <summary>
	/// Czyœci obiekty aktywuje destruktor
	/// </summary>
	void clearFactory();
	/// <summary>
	/// Zwraca Item którego podajemy ID
	/// </summary>
	/// <param name="ID">Ite itemu</param>
	/// <returns>Zwra kopiê itemu</returns>
	Item* getObject(int ID);
	/// <summary>
	/// Zwraca obiekt po nazwie
	/// </summary>
	/// <param name="name">nazwa obiektu jaki chcemy</param>
	/// <returns>obiekt</returns>
	Item* getObject(std::string name);
	/// <summary>
	/// Rysuje obiekt przedmiotu w podanej pozycji
	/// </summary>
	/// <param name="ID">Id przedmiotu</param>
	/// <param name="pos">Pozycja gdzie ma byæ narysowany przedmiot</param>
	void drawObjectAt(int ID, Rectangle pos);

	std::string getDescription(int ID) { return objects[ID]->getDesctription(); }

	void drawItemDescription(int ID, int x, int y);

	bool isStacableItem(int ID);
};

