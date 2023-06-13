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
};

