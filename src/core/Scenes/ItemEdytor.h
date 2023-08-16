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
public:
    ItemEdytor();

	~ItemEdytor();

	virtual void start();

	virtual void update(float deltaTime);

	void newItem();

	void removeItem();

	virtual void draw();
};

