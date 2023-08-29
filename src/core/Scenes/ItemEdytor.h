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


class ItemEdytor :
    public Scene
{
	ItemProperty item;
	std::list<Element*> elements;
	std::vector<ItemProperty*> items;
	Element* lastPressed = NULL;
	Rectangle itemDraw= { 500,100,600,600 };
	int holdPoint = -1;
	Rectangle itemsDraw = { 1200,100,300,600 };
public:
    ItemEdytor();

	~ItemEdytor();

	virtual void start();

	virtual void update(float deltaTime);

	void newItem();

	void removeItem();

	virtual void draw();

	Rectangle itemPos(int i);

	void setItemData();
	void lastElementPressed();
	void checkPress();
	void itemDrawPointsClick();
	void itemDrawPointsHold();
	void itemDrawShow();
	
};

