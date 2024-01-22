#pragma once
#include <list>
#include "../../../GameObjects/GameObject.h"
#define allTreeIf if (tree) for (int i = 0; i < 4; i++)tree[i]
#define allTree	for (int i = 0; i < 4; i++)tree[i]
#define allObjects GameObject* o : objects


class QuadTree
{
	Rectangle pos;
	std::list<GameObject*> objects;
	QuadTree** tree = NULL;
	/// <summary>
	/// Metoda sluzaca do dopisywaniu do listy obiektow na odpowiednim obszarze gry
	/// </summary>
	/// <param name="pos"></param>
	/// <param name="objs"></param>
	void getObjectsAt(Rectangle pos,std::list<GameObject*> &objs);
	/// <summary>
	/// Metoda sluzaca do rozwiniecia lisci drzewa w galaz
	/// </summary>
	void openTree();
	/// <summary>
	///	Metoda sluzaca do zamykania galezi w powrot do stanu liscia
	/// </summary>
	/// <summary>
	/// Metoda sluzaca do aktualizowania pozycji obiektu w strukturze drzewa
	/// </summary>
	/// <param name="obj">Obiekt do aktualizacji pozycji</param>
	void closeTree();
public:
	/// <summary>
	/// Konstruktor domyslny struktury drzewa czworkowego
	/// </summary>
	/// <param name="pos"></param>
	QuadTree(Rectangle pos);
	/// <summary>
	/// Destruktor drzewa czworkowego
	/// </summary>
	~QuadTree();
	/// <summary>
	/// Dodaje obiekt do drzewa do odpowiednich lisci i galezi
	/// </summary>
	/// <param name="obj"></param>
	void addObj(GameObject* obj);
	/// <summary>
	/// Usuwa obiekt z lisci i galezi drzewa
	/// </summary>
	/// <param name="obj"></param>
	void removeObj(GameObject* obj);

	void updatePos(GameObject* obj);
	/// <summary>
	/// Sprawdza czy dany lisc i galaz posiada dany obiekt
	/// </summary>
	/// <param name="obj"></param>
	/// <returns></returns>
	bool hasObj(GameObject* obj);
	/// <summary>
	/// Zwraca liste obiektow na danej pozycji
	/// </summary>
	/// <param name="pos">Obszar z jakiego chcemy zczytac obiekty</param>
	/// <returns>Lista obiektow</returns>
	std::list<GameObject*> getObjectsAt(Rectangle pos);
	/// <summary>
	/// Metoda pozwalajaca narysowac struktury drzewa na mapie
	/// </summary>
	void draw();
};

