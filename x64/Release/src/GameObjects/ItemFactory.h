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
	/// <summary>
	/// Zwraca opis itemu
	/// </summary>
	/// <param name="ID">ID Itemu</param>
	/// <returns>Opis przedmiotu</returns>
	std::string getDescription(int ID);
	/// <summary>
	/// Rysuje opis przedmiotu od podanych kordynatów
	/// </summary>
	/// <param name="ID">ID Itemu</param>
	/// <param name="x">Pozycja x</param>
	/// <param name="y">Pozycja y</param>
	void drawItemDescription(int ID, int x, int y);
	/// <summary>
	/// Zrwaca wilkoœæ opisu textu ile zajmuje w pixelach
	/// </summary>
	/// <param name="ID">ID Itemu</param>
	/// <returns>Zwraca vektor jak du¿y jest text x szerokosc y wysokoœæ z vektora</returns>
	Vector2 itemDescriptionSize(int ID);
	/// <summary>
	/// Zwraca czy item mo¿na stakowaæ
	/// </summary>
	/// <param name="ID"></param>
	/// <returns></returns>
	bool isStacableItem(int ID);
	/// <summary>
	/// Zwraca ile jest obiektów w fabryce
	/// </summary>
	/// <returns>Iloœæ obiektów</returns>
	int getSize() { return objects.size(); }
	/// <summary>
	/// Wczytuje odpowiedni jêzyk dla przedmiotów
	/// </summary>
	/// <param name="Language">Jezyk jaki chcemy wszystaæ</param>
	void loadLanguage(std::string Language);

	int getItemVaiue(int ID);

	bool isStacable(int ID);
};

