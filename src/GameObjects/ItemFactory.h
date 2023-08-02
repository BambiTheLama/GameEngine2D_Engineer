#pragma once
#include "Items/Item.h"
#include <vector>
#include "Factory.h"

#define Items ItemFactory::getFactory()
/// <summary>
/// Fabryka Item�w zwraca nam kopi� obiektu
/// </summary>
class ItemFactory :Factory
{
	std::vector<Item*> objects;
	static ItemFactory* factory;
	/// <summary>
	/// Konstruktor domy�lny
	/// </summary>
	ItemFactory();
	/// <summary>
	/// Destruktor
	/// </summary>
	~ItemFactory();
public:
	/// <summary>
	/// Zwraca fabryk�
	/// </summary>
	/// <returns></returns>
	static ItemFactory* getFactory();
	/// <summary>
	/// Czy�ci obiekty aktywuje destruktor
	/// </summary>
	void clearFactory();
	/// <summary>
	/// Zwraca Item kt�rego podajemy ID
	/// </summary>
	/// <param name="ID">Ite itemu</param>
	/// <returns>Zwra kopi� itemu</returns>
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
	/// <param name="pos">Pozycja gdzie ma by� narysowany przedmiot</param>
	void drawObjectAt(int ID, Rectangle pos);

	std::string getDescription(int ID) { return objects[ID]->getDesctription(); }

	void drawItemDescription(int ID, int x, int y);

	bool isStacableItem(int ID);
};

