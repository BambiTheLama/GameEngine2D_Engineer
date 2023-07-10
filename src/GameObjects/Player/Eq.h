#pragma once
#include "../Items/Item.h"
#define EqWight 10
#define EqHeight 4
#define EqSize 32
#define EqSpacing 10
#define EqStartX 64
#define EqStartY 32
enum class sortBy {
	ID,NAME,Type
};

class Eq
{
	int usingItem = 0;
	Item* items[EqHeight][EqWight];
public:
	Eq();

	void sortItems(sortBy typ);

	bool useItem();

	bool addItem(Item* item);

	Item* getItem(int slotX, int slotY) { return items[slotY][slotX]; }

	void draw(bool fullEq);
};

