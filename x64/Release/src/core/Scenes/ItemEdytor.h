#pragma once
#include "Scene.h"
#include "../../GameObjects/Items/Item.h"
#include "../../GameObjects/Items/Tool/ToolItem.h"
#include "../Elements/Element.h"
#include "json.hpp"
#include "ItemEdytorStruct/ItemProperty.h"
#include <list>
#include <vector>
#include <iostream>
#include "../Elements/CheckBoxOpenElements.h"
#include "../Elements/AddItem.h"
#include "../Elements/RemoveItem.h"
/// <summary>
/// Klasa odpowiedzialna za scene z edytora przedmiotow
/// </summary>
class ItemEdytor :
    public Scene, public AdderEdytor, public RemoverEdytor
{
	ItemProperty* item=NULL;
	std::list<Element*> elements;
	std::vector<ItemProperty*> items;
	Element* lastPressed = NULL;
	Rectangle itemDraw= { 500,100,600,600 };
	int holdPoint = -1;
	Rectangle itemScroll = { 1510,169,10,550 };
	Rectangle itemsSelect = { 1200,169,300,600 };
	CheckBoxOpenElements* first = NULL;
	int firstItem = 0;
	const int howManyElementsInRow = 5;
	const int howManyElementsRow = 9;
	const int itemsBoxSize = 64;
	const int itemsBoxSpacing = 10;

public:
    /// <summary>
    /// Konstruktor domyslny sceny
    /// </summary>
    ItemEdytor();
	/// <summary>
	/// Destruktor domyslny sceny
	/// </summary>
	~ItemEdytor();
	/// <summary>
	/// Wczytuje dane z pliku
	/// </summary>
	void loadDataFromFile();
	/// <summary>
	/// Zapisuje dane do pliku
	/// </summary>
	void saveData();

	void start();

	void update(float deltaTime);
	/// <summary>
	/// Doaje nowy przedmiot 
	/// </summary>
	void addItem();
	/// <summary>
	/// Usuwa przedmiot
	/// </summary>
	void removeItem();

	void popBackItem();

	virtual void draw();
	/// <summary>
	/// Zwraca pozycje obiektu na liscie wszystkich obiektow w bocznym menu
	/// </summary>
	/// <param name="i">index obiektu</param>
	/// <returns></returns>
	Rectangle itemPos(int i);
	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	Rectangle getScrollMovingPos();
	/// <summary>
	/// Metoda sluzaca za usuniecia ostatniego elementu z danego miejsca w obiekcie
	/// </summary>
	void lastElementPressed();
	/// <summary>
	/// Sprawdza plikniecie 
	/// </summary>
	void checkPress();

	bool itemDrawPointsClick();

	bool itemsSelectPointClick();
	/// <summary>
	/// Rysuje trzymany punk ktory sluzy za interkacje obiektu
	/// </summary>
	void itemDrawPointsHold();

	void itemDrawShow();
	/// <summary>
	/// Wczytuje nowy przedmiot od podanym id
	/// </summary>
	/// <param name="i"></param>
	void loadNewItem(int i);
};

