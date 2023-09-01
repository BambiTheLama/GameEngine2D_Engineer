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

class ItemEdytor :
    public Scene
{
	ItemProperty* item=NULL;
	std::list<Element*> elements;
	std::vector<ItemProperty*> items;
	Element* lastPressed = NULL;
	Rectangle itemDraw= { 500,100,600,600 };
	int holdPoint = -1;
	Rectangle itemsSelect = { 1200,169,300,600 };
	CheckBoxOpenElements* first = NULL;
	int firstItem = 0;
public:
    ItemEdytor();

	~ItemEdytor();

	virtual void start();

	virtual void update(float deltaTime);

	void newItem();

	void removeItem();

	void addItem();

	void popBackItem();

	virtual void draw();

	Rectangle itemPos(int i);

	void lastElementPressed();
	void checkPress();
	void itemDrawPointsClick();
	void itemsSelectPointClick();
	void itemDrawPointsHold();
	void itemDrawShow();
	void loadNewItem(int i);
	int getHowManyElementsInTheRow();
};

