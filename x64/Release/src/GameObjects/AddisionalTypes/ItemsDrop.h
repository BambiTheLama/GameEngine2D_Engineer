#pragma once
#include "../Items/Item.h"
#include "../ItemFactory.h"
#include <vector>
/// <summary>
/// Struktura kt�ra przechowuje dane odno�nie dropu itemu jak szansa ilo�� i ID itemu
/// </summary>
struct DropItem
{
	int ID;				//ID itemu kt�rego mo�emy dosta�
	int min;			//Minimalna ilo�� item�w
	int max;			//Maksymalna ilo�� item�w 
	float dropChanse;	//Pomi�dzy <0;100> wyra�ona w % dok�adko�� do 0.001
	bool wasDroped() {
		return ((float)(rand() % 100) + (float)(rand() % 1000) / 1000.f) < dropChanse;
	}
	int howMuch() {
		if (min >= max)
			return min;
		return rand() % (max - min + 1) + min;
	}

};
enum class ObjectType;

class ItemsDrop {
	std::vector<DropItem> items;
	void copyDataFrom(ItemsDrop& drops);
public:
	ItemsDrop();

	ItemsDrop(ObjectType type,int ID);

	ItemsDrop(ItemsDrop& drops);

	void addItemToDrop(int ID, float chanse, int min, int max);

	void clearItemsDrop() { items.clear(); }

	std::vector<Item*> getDrop();
};