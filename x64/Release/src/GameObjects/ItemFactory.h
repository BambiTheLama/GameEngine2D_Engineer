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
	/// <summary>
	/// Zwraca opis itemu
	/// </summary>
	/// <param name="ID">ID Itemu</param>
	/// <returns>Opis przedmiotu</returns>
	std::string getDescription(int ID);
	/// <summary>
	/// Rysuje opis przedmiotu od podanych kordynat�w
	/// </summary>
	/// <param name="ID">ID Itemu</param>
	/// <param name="x">Pozycja x</param>
	/// <param name="y">Pozycja y</param>
	void drawItemDescription(int ID, int x, int y);
	/// <summary>
	/// Zrwaca wilko�� opisu textu ile zajmuje w pixelach
	/// </summary>
	/// <param name="ID">ID Itemu</param>
	/// <returns>Zwraca vektor jak du�y jest text x szerokosc y wysoko�� z vektora</returns>
	Vector2 itemDescriptionSize(int ID);
	/// <summary>
	/// Zwraca czy item mo�na stakowa�
	/// </summary>
	/// <param name="ID"></param>
	/// <returns></returns>
	bool isStacableItem(int ID);
	/// <summary>
	/// Zwraca ile jest obiekt�w w fabryce
	/// </summary>
	/// <returns>Ilo�� obiekt�w</returns>
	int getSize() { return objects.size(); }
	/// <summary>
	/// Wczytuje odpowiedni j�zyk dla przedmiot�w
	/// </summary>
	/// <param name="Language">Jezyk jaki chcemy wszysta�</param>
	void loadLanguage(std::string Language);

	int getItemVaiue(int ID);

	bool isStacable(int ID);
};

