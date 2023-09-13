#pragma once
#include "Scene.h"
#include "../../GameObjects/Items/Item.h"
#include "../../GameObjects/Items/Tool/ToolItem.h"
#include "../Elements/Element.h"
#include "../../json.hpp"
#include "ItemEdytorStruct/ItemProperty.h"
#include <list>
#include <vector>
#include <iostream>
#include "../Elements/CheckBoxOpenElements.h"
#include "../Elements/AddItem.h"
#include "../Elements/RemoveItem.h"

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
    ItemEdytor();

	~ItemEdytor();

	void loadDataFromFile();

	void saveData();

	void start();

	void update(float deltaTime);

	void newItem();

	void removeItem();

	void addItem();

	void popBackItem();

	virtual void draw();

	Rectangle itemPos(int i);

	Rectangle getScrollMovingPos();

	void lastElementPressed();

	void checkPress();

	bool itemDrawPointsClick();

	bool itemsSelectPointClick();

	void itemDrawPointsHold();

	void itemDrawShow();

	void loadNewItem(int i);
};

