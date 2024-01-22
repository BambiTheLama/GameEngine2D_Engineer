#pragma once
#include "../Items/Item.h"
struct ItemSell {
	Item* item=NULL;
	int numberOfItem = 1;
	int prise = 1;
	ItemSell(){}
	ItemSell(Item* item, int numberOfItem, int prise);
	ItemSell(ItemSell& itemSell);
	~ItemSell();
	void saveToJson(nlohmann::json& j);
	void readFromJson(nlohmann::json& j);
};

class Shop
{
	std::list<ItemSell*> itemToSell;
	const float spacing = 10;
	const float elementSize = 64;
	const int maxItemsInRow = 8;
	const char* text = "SHOP";
	const int textH = textSize(text, textStandardSize2).y;
protected:
	Shop(Shop& s);
public:
	Shop();

	~Shop();

	void addItem(Item* item, int prise, int numberOfItem);

	Rectangle getElementPos(int x, int y, int i);

	Item* updateShop(Vector2 mousePos,int x,int y,int &money);

	void drawShop(int x, int y);

	void saveToJson(nlohmann::json &j);

	void readFromJson(nlohmann::json& j);
};

