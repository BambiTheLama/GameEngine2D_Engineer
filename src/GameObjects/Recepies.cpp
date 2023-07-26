#include "Recepies.h"
#include "ItemFactory.h"

Recepies::Recepies(int finalItemID)
{
	this->finalItemID = finalItemID;
}

void Recepies::addItemToRecepies(int ID, int howMany)
{
	ItemToRecepies items;
	items.ItemID = ID;
	items.howMany = howMany;
	itemsToBuildItem.push_back(items);
}

Item* Recepies::craftItem(Item*** items,int w,int h)
{

}