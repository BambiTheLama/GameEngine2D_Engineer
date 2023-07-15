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
	int usingItem = 0, usingItemX = 0, usingItemY = 0;
	Item*** items = NULL;
public:
	Eq();

	~Eq();

	void sortItems(sortBy typ);

	bool useItem();

	bool addItem(Item* item);

	Item* getItem(int slotX, int slotY) { return items[slotY][slotX]; }

	Item* getUsingItem() { return items[usingItemY][usingItemX]; }

	void updateItemPos(Vector2 movePos);

	void update();

	void draw();

	void draw(bool fullEq);
};

