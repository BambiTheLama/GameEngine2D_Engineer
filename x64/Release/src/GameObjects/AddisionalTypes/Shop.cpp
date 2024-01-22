#include "Shop.h"
#include "../ItemFactory.h"
#include "../../core/Scenes/GameScene.h"
ItemSell::ItemSell(Item* item, int numberOfItem, int prise)
{
	this->item = item;
	this->prise = prise;
	this->numberOfItem = numberOfItem;
}
ItemSell::ItemSell(ItemSell& itemSell)
{
	this->item = itemSell.item->clone();
	this->prise = itemSell.prise;
	this->numberOfItem = itemSell.numberOfItem;
}
ItemSell::~ItemSell()
{
	if (item)
		delete item;
}
void ItemSell::saveToJson(nlohmann::json& j)
{
	j["prise"] = prise;
	j["numberOfItem"] = numberOfItem;
	j["ItemID"] = item->getID();
}
void ItemSell::readFromJson(nlohmann::json& j)
{
	if(j.contains("prise"))
		prise = j["prise"];
	if (j.contains("numberOfItem"))
		numberOfItem = j["numberOfItem"];
	if (item)
	{
		delete item;
		item = NULL;
	}
	if (j.contains("ItemID"))
	{
		item = Items->getObject((int)j["ItemID"]);
	}

}

Shop::Shop(Shop& s)
{
	itemToSell.clear();
	for (auto i : s.itemToSell)
	{
		itemToSell.push_back(new ItemSell(*i));
	}
}

Shop::Shop()
{

}

Shop::~Shop()
{
	for (auto i : itemToSell)
		delete i;
	itemToSell.clear();
}

void Shop::addItem(Item* item, int prise, int numberOfItem)
{
	itemToSell.push_back(new ItemSell(item, numberOfItem, prise));
}
Rectangle Shop::getElementPos(int x, int y, int i)
{

	return { x + (i % maxItemsInRow) * (spacing + elementSize),
		y + (int)(i / maxItemsInRow) * (spacing + elementSize),
			elementSize,elementSize };
}

Item* Shop::updateShop(Vector2 mousePos, int x, int y,int &money)
{
	ItemSell* toRemove = NULL;
	Item* itemToRet = NULL;
	int i = 0;
	y += textH;
	x += spacing;
	for (auto item : itemToSell)
	{
		Rectangle elementPos = getElementPos(x, y, i);
		if (CheckCollisionPointRec(mousePos, getElementPos(x, y, i)))
		{
			if (money < item->prise)
				return NULL;
			money -= item->prise;
			item->numberOfItem--;
			if (item->numberOfItem <= 0)
				toRemove = item;
			itemToRet = item->item->clone();
		}
		i++;
	}
	if(toRemove)
		itemToSell.remove(toRemove);
	delete toRemove;
	return itemToRet;
}

void Shop::drawShop(int x, int y)
{
	int i = 0;
	int xItems = maxItemsInRow;
	int yItems = ((itemToSell.size()-1) / maxItemsInRow)+ 1;
	if (itemToSell.size() <= 0)
		yItems = 1;
	Rectangle shopWindow = { x,y,xItems * (spacing + elementSize)+ spacing,yItems * (spacing + elementSize) + textH };
	DrawRectangleRec(shopWindow, BLUE);
	DrawRectangleLinesEx(shopWindow, 3, BLACK);

	DrawTextWithOutline(text, x + spacing, y + 3, textStandardSize2, WHITE, BLACK);
	y += textH;
	x += spacing;
	for (auto item:itemToSell)
	{
		Rectangle elementPos = getElementPos(x, y, i);
		DrawRectangleRec(elementPos, DARKPURPLE);
		DrawRectangleLinesEx(elementPos,3, BLACK);
		if (item->item)
		{
			item->item->drawAt(elementPos);
		}
		DrawTextWithOutline(TextFormat("%d$\n\n%d",item->prise,item->numberOfItem), elementPos.x+3, elementPos.y+3, textStandardSize, WHITE, BLACK);

		i++;
	}
	i = 0;
	for (auto item : itemToSell)
	{
		Rectangle elementPos = getElementPos(x, y, i);
		if (item->item)
		{
			if (CheckCollisionPointRec(Game->worldToScreanPos(Game->getCursorPos()), elementPos))
				item->item->drawDescription(elementPos.x, elementPos.y + elementPos.height);
		}
		i++;
	}
}

void Shop::saveToJson(nlohmann::json& j)
{
	int i = 0;
	for (auto item : itemToSell)
	{
		item->saveToJson(j["SHOP"][i]);
		i++;
	}

}

void Shop::readFromJson(nlohmann::json& j)
{
	if (!j.contains("SHOP"))
		return;
	for (auto item : itemToSell)
	{
		if(item)
			delete item;
	}
	itemToSell.clear();
	int i = 0;
	for (int i = 0; i < j["SHOP"].size(); i++)
	{
		ItemSell* itemToSell = new ItemSell(NULL, 0, 0);
		itemToSell->readFromJson(j["SHOP"][i]);
		this->itemToSell.push_back(itemToSell);
	}
}