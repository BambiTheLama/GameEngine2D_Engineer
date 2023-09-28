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
	float dropChanse;	//Pomi�dzy <0;100> wyra�ona w % dok�adko�� do 0.0001
	bool wasDroped() {
		return (rand() % 1000000 / 10000) < dropChanse;
	}
	int howMuch() {
		return rand() % (max - min) + min;
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

	std::vector<Item*> getDrop();
};