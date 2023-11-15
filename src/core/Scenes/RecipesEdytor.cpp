#include "RecipesEdytor.h"
#include "json.hpp"
#include <fstream>
#include "../../GameObjects/ItemFactory.h"
#include "../Elements/LineColliderCheckBox.h"
#include "../Elements/CheckBoxOpenElements.h"
#include "../Elements/RectangleEnter.h"
#include "../Elements/VectorEnter.h"
#include "../Elements/FloatEnter.h"
#include "../Elements/TextEnter.h"
#include "../Elements/CheckBox.h"
#include "../Elements/IntEnter.h"
#include "../Elements/Add.h"
#include "../Elements/Remove.h"
#include "../Elements/EnumEnter.h"
#include "../Elements/AddItem.h"
#include "../Elements/RemoveItem.h"
#include <iostream>
#include "Menu.h"
#include "../Engine.h"

RecipesEdytor::RecipesEdytor():Scene()
{
	SetExitKey(0);
	usingRecepies = new Recipes(0);

	Rectangle buttons = recepiesStartPos;
	buttons.y = 85;
	buttons.width = elementSize;
	buttons.height = elementSize;
	elements.push_back(new Remove(buttons, &firstRecepies, recepiesElementsInRow));
	buttons.x += spacing + elementSize;
	elements.push_back(new Add(buttons, &firstRecepies, recepiesElementsInRow));
	buttons.x += spacing + elementSize;
	elements.push_back(new AddItem(buttons, this));
	buttons.x += spacing + elementSize;
	elements.push_back(new RemoveItem(buttons, this));
	buttons.x += spacing + elementSize;

	recepiesStartPos.width = recepiesElementsInRow * (spacing + elementSize);
	recepiesStartPos.height = recepiesElementsRow * (spacing + elementSize);
	recepy = ItemToRecipes();
	
	Rectangle pos = { getRecepiesComponetPos(recepiesComponetInRow-1).x + 2*elementSize,600,200,32};
	itemBuildingPos.x = pos.x;
	pos.y = itemBuildingPos.y + itemBuildingPos.height + spacing;
	elements.push_back(new IntEnter(pos, "Item ID:", &recepy.itemID));
	pos.y += pos.height + spacing;
	elements.push_back(new IntEnter(pos, "How Many:", &recepy.howMany));
	pos.y += pos.height + spacing;
	finalItemBuildingPos = itemBuildingPos;
	finalItemBuildingPos.y = pos.y;

	pos.y = finalItemBuildingPos.y + finalItemBuildingPos.height + spacing;
	elements.push_back(new IntEnter(pos, "Item ID:", &usingRecepies->finalItemID));
	pos.y += pos.height + spacing;
	elements.push_back(new IntEnter(pos, "How Many:", &usingRecepies->howManyItems));
	pos.y += pos.height + spacing;
	elements.push_back(new EnumEnter(pos, "Where craft:", &craftingStation,
		(int)CraftingStationEnum::EnumSize,getCraftingStationDescription()));
	pos.y += pos.height + spacing;

	loadDataFromFile();
}
RecipesEdytor::~RecipesEdytor()
{
	saveData();
	for (int i = 0; i < recepies.size(); i++)
	{
		delete recepies[i];
	}
	for (Element* e : elements)
		delete e;
	elements.clear();
	delete usingRecepies;
}

void RecipesEdytor::loadDataFromFile()
{
	for (int i = 0; i < recepies.size(); i++)
	{
		delete recepies[i];
	}
	recepies.clear();

	nlohmann::json j;
	std::ifstream reader;
	reader.open("Recepies.json");
	if (reader.is_open())
	{
		reader >> j;

	}
	reader.close();

	for (int i = 0; i < j.size(); i++)
	{
		recepies.push_back(new Recipes(j, i));
	}
	if (recepies.size() <= 0)
		recepies.push_back(new Recipes(0));
	usingRecepies->copyItemData(*recepies[0]);
	recepiesId = 0;
}

void RecipesEdytor::saveData()
{
	loadNewItemRecepies(-1);
	nlohmann::json j;
	for (int i = 0; i < recepies.size(); i++)
	{
		recepies[i]->saveToJson(j, i);
	}
	std::ofstream writer;
	std::cout << j.dump(2) << std::endl;
	writer.open("Recepies.json");
	writer << j.dump(2) << std::endl;
	writer.close();
}

void RecipesEdytor::start()
{
	for (auto* e : elements)
		e->updatePos();
}
void RecipesEdytor::draw()
{
	int n = recepies.size()- firstRecepies;
	if (n > recepiesElementsInRow * recepiesElementsRow)
		n = recepiesElementsInRow * recepiesElementsRow;
	ItemFactory* factory = Items;
	DrawRectangleRec(itemBuildingPos, WHITE);
	DrawRectangleLinesEx(itemBuildingPos, 2, BLACK);
	factory->drawObjectAt(recepy.itemID,itemBuildingPos);

	DrawRectangleRec(finalItemBuildingPos, WHITE);
	DrawRectangleLinesEx(finalItemBuildingPos, 2, BLACK);
	factory->drawObjectAt(usingRecepies->getFinalItemID(), finalItemBuildingPos);
	for (int i = 0; i < n; i++)
	{
		Rectangle pos = getRecepiesElementsPos(i);
		int itemId = recepies[i + firstRecepies]->getFinalItemID();
		DrawRectangleRec(pos, WHITE);
		DrawRectangleLinesEx(pos, 2, BLACK);
		factory->drawObjectAt(itemId, pos);
		DrawTextWithOutline(TextFormat("%d", i + firstRecepies), pos.x, pos.y, textStandardSize, BLACK, WHITE);
	}
	if (usingRecepies)
	{
		ItemFactory* factory=Items;
		std::vector<ItemToRecipes> buildItems = usingRecepies->getItemsToBuild();
		for (int i = 0; i < buildItems.size(); i++)
		{
			int ID = buildItems[i].itemID;
			Rectangle pos = getRecepiesComponetPos(i);
			DrawRectangleRec(pos, WHITE);
			DrawRectangleLinesEx(pos, 2, BLACK);
			factory->drawObjectAt(ID, pos);
			DrawTextWithOutline(TextFormat("%d\n%d", ID, buildItems[i].howMany)
				, pos.x , pos.y + pos.height, textStandardSize, BLACK, WHITE);

		}
		Rectangle pos = getRecepiesComponetPos(buildItems.size());
		DrawRectangleRec(pos, WHITE);
		DrawRectangleLinesEx(pos, 2, BLACK);
		DrawTextWithOutline("+?", pos.x, pos.y, textStandardSize, BLACK, WHITE);
	}
	
	std::list<Element*>::iterator it = elements.end();
	do {
		it--;
		(*it)->draw();
	} while (*it != *elements.begin());

}
void RecipesEdytor::update(float deltaTime)
{
	if (IsKeyReleased(KEY_ESCAPE))
	{
		Engine::setScene(new Menu());
		return;
	}

	for (Element* e : elements)
		e->update();
	if (IsKeyDown(KEY_LEFT_CONTROL))
	{
		if (IsKeyPressed(KEY_S))
			saveData();
		else if (IsKeyDown(KEY_L))
			loadDataFromFile();
	}
	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		if (lastPressed)
			lastPressed->unPress();
		lastPressed = NULL;
		for (Element* e : elements)
		{
			if (e->press())
			{
				lastPressed = e;
				break;
			}
		}
		if (lastPressed)
			return;
		if (checkPressRecepiesElements())
			return;	
		if (checkPressRecepiesComponets())
			return;
	}
	if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
		if (checkPressRecepiesComponets())
			return;

}

void RecipesEdytor::loadNewItemRecepies(int i)
{
	usingRecepies->whereToCraft = (CraftingStationEnum)craftingStation;
	if (recepiesId >= 0 && recepiesId <= recepies.size())
	{
		loadNewItemComponet(0);
		recepies[recepiesId]->copyItemData(*usingRecepies);
	}
	if (i >= 0 && i < recepies.size())
	{
		usingRecepies->copyItemData(*recepies[i]);
		recepiesId = i;
		craftingStation = (int)usingRecepies->whereToCraft;
		usingComponet = -1;
		loadNewItemComponet(0);
	}

}
void RecipesEdytor::loadNewItemComponet(int i)
{
	if (usingComponet >= 0 && usingComponet < usingRecepies->itemsToBuildItem.size())
	{
		ItemToRecipes r = usingRecepies->itemsToBuildItem[usingComponet];
		r.howMany = recepy.howMany;
		r.itemID = recepy.itemID;
		usingRecepies->itemsToBuildItem[usingComponet] = r;
	}
	if (i >= 0 && i < usingRecepies->itemsToBuildItem.size())
	{
		recepy.itemID = usingRecepies->itemsToBuildItem[i].itemID;
		recepy.howMany = usingRecepies->itemsToBuildItem[i].howMany;
		usingComponet = i;
	}
}
void RecipesEdytor::removeItemComponet(int i)
{
	loadNewItemComponet(-1);
	int n = usingRecepies->itemsToBuildItem.size()-1;
	for (int k = i; k < n; k++)
		usingRecepies->itemsToBuildItem[k] = usingRecepies->itemsToBuildItem[k + 1];
	if(n>0)
		usingRecepies->itemsToBuildItem.pop_back();
}

Rectangle RecipesEdytor::getRecepiesElementsPos(int i)
{
	Rectangle pos;
	pos.width = elementSize;
	pos.height = elementSize;
	pos.x = recepiesStartPos.x + (i % recepiesElementsInRow) * (spacing + elementSize);
	pos.y = recepiesStartPos.y + (i / recepiesElementsInRow) * (spacing + elementSize);
	return pos;
}

Rectangle RecipesEdytor::getRecepiesComponetPos(int i)
{
	Rectangle pos;
	pos.width = elementSize;
	pos.height = elementSize;
	pos.x = recepiesComponetPos.x + (i % recepiesComponetInRow) * (spacing + elementSize);
	pos.y = recepiesComponetPos.y + (i / recepiesComponetInRow) * (spacing + elementSize * 2);
	return pos;
}

bool RecipesEdytor::checkPressRecepiesElements()
{
	Vector2 mouse = GetMousePosition();
	if (!CheckCollisionPointRec(mouse, recepiesStartPos))
		return false;
	int n = recepies.size() - firstRecepies;
	if (n > recepiesElementsInRow * recepiesElementsRow)
		n = recepiesElementsInRow * recepiesElementsRow;

	for (int i = 0; i < n; i++)
	{
		if (CheckCollisionPointRec(mouse, getRecepiesElementsPos(i)))
		{
			loadNewItemRecepies(i + firstRecepies);
			return true;
		}
	}
	return false;
}

bool RecipesEdytor::checkPressRecepiesComponets()
{
	Vector2 mouse = GetMousePosition();
	Rectangle pos = recepiesComponetPos;
	Rectangle pos2 = getRecepiesComponetPos(usingRecepies->getItemsToBuild().size());
	int n = usingRecepies->getItemsToBuild().size();
	pos.width += (elementSize + spacing) * ((recepiesComponetInRow-1) % recepiesComponetInRow);
	pos.height += (elementSize*2 + spacing) * (n / recepiesComponetInRow);
	if (!CheckCollisionPointRec(mouse, pos))
		return false;
	if (n > recepiesElementsInRow * recepiesElementsRow)
		n = recepiesElementsInRow * recepiesElementsRow;

	for (int i = 0; i < n; i++)
	{
		if (CheckCollisionPointRec(mouse, getRecepiesComponetPos(i)))
		{
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
				loadNewItemComponet(i);
			else if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
				removeItemComponet(i);
			return true;
		}
	}
	Rectangle checkPos = getRecepiesComponetPos(n);
	if (CheckCollisionPointRec(mouse, checkPos))
	{
		addRecepyComponet();
		return true;
	}

	return false;
}
void RecipesEdytor::addRecepyComponet()
{
	usingRecepies->addItemToRecipes(0);
	loadNewItemRecepies(recepiesId);
}
void RecipesEdytor::removeItem()
{
	int ID = recepiesId;
	if (ID >= 0 && ID < recepies.size())
	{
		if (recepies[ID])
		{
			delete recepies[ID];
			recepies[ID] = NULL;
		}
		for (int i = ID; i < recepies.size() - 1; i++)
		{
			recepies[i] = recepies[i + 1];
		}
		recepies.pop_back();
		if (recepies.size() <= 0)
		{
			addItem();
			recepiesId = 0;
			
		}
		else if(recepiesId>=recepies.size())
		{
			recepiesId = recepies.size() - 1;
		}
		usingRecepies->copyItemData(*recepies[recepiesId]);

	}
}

void RecipesEdytor::addItem()
{
	recepies.push_back(new Recipes(0));
}