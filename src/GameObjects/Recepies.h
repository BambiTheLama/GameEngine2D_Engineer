#pragma once
#include <vector> 

class Item;
struct ItemToRecepies {
	int ItemID, howMany;
};
class Recepies
{
	int finalItemID;
	std::vector<ItemToRecepies> itemsToBuildItem;
public:
	Recepies(int finalItemID);

	void addItemToRecepies(int ID, int howMeny=1);

	int getFinalItemID() { return finalItemID; }

	std::vector<ItemToRecepies> getTtemsToBuild()const { return itemsToBuildItem; }

	Item* craftItem(Item*** items, int w, int h);
};

