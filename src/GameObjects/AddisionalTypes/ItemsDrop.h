#pragma once
#include "../Items/Item.h"
#include "../ItemFactory.h"
#include <vector>
/// <summary>
/// Struktura która przechowuje dane odnoœnie dropu itemu jak szansa iloœæ i ID itemu
/// </summary>
struct DropItem
{
	int ID;				//ID itemu którego mo¿emy dostaæ
	int min;			//Minimalna iloœæ itemów
	int max;			//Maksymalna iloœæ itemów 
	float dropChanse;	//Pomiêdzy <0;100> wyra¿ona w % dok³adkoœæ do 0.0001
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