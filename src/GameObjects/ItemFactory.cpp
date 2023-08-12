#include "ItemFactory.h"
#include "Items/Item.h"
#include "Items/StackItem.h"
#include "Items/Tool/ToolItem.h"
#include "Items/Weapon/Ammo.h"
#include "Items/Weapon/Bow.h"
ItemFactory* ItemFactory::factory = NULL;

ItemFactory::ItemFactory()
{
	int blockStackSize = 100;
	objects = std::vector<Item*>();
	objects.push_back(new StackItem({ 0,0,32,32 }, "Wood", blockStackSize));
	objects.push_back(new StackItem({ 0,0,32,32 }, "Plank", blockStackSize));
	objects.push_back(new StackItem({ 0,0,32,32 }, "Dirt", blockStackSize));
	objects.push_back(new StackItem({ 0,0,32,32 }, "Sand", blockStackSize));
	objects.push_back(new StackItem({ 0,0,32,32 }, "Stone", blockStackSize));
	ToolItem* tool = new ToolItem({ 0,0,32,32 }, "Axe", ToolType::Axe, 30);
	Vector2 points[4];
	points[0] = { 14,31 };
	points[1] = { 31,20 };
	points[2] = { 19,10 };
	points[3] = { 9,26 };
	tool->setStartPoints(points);
	objects.push_back(tool);
	tool = new ToolItem({ 0,0,32,32 }, "Pickaxe", ToolType::Pickaxe, 30);
	points[0] = { 5,28 };
	points[1] = { 17,31 };
	points[2] = { 29,16 };
	points[3] = { 28,6 };
	tool->setStartPoints(points);
	objects.push_back(tool);
	tool = new ToolItem({ 0,0,32,32 }, "Hoe");
	points[0] = { 19,30 };
	points[1] = { 31,12 };
	points[2] = { 29,8 };
	points[3] = { 13,25 };
	tool->setStartPoints(points);
	objects.push_back(tool);
	tool = new ToolItem({ 0,0,32,32 }, "Shovel", ToolType::Shovel, 30);
	objects.push_back(tool);
	points[0] = { 14,24};
	points[1] = { 24,31};
	points[2] = { 31,23};
	points[3] = { 23,15};
	tool->setStartPoints(points);
	tool = new ToolItem({ 0,0,32,32 }, "Sword");
	points[0] = { 7,12 };
	points[1] = { 27,31 };
	points[2] = { 31,28 };
	points[3] = { 12,8 };

	tool->setStartPoints(points);
	objects.push_back(tool);

	objects.push_back(new Bow({ 0,0,32,32 }, "Bow"));
	objects.push_back(new Ammo({ 0,0,32,32 }, "Arrow", AmmoType::Arrow));
	
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->ID = i;
	}
	printf("[FactoryItem]: Stworzono fabryke itemow\n");
}

ItemFactory::~ItemFactory()
{
	for (auto i:objects)
		delete i;
	objects.clear();
	printf("[FactoryItem]: Usunieto fabryke itemow\n");
}
void ItemFactory::clearFactory()
{
	if (factory != NULL)
		delete factory;
}

ItemFactory* ItemFactory::getFactory()
{
	if (factory == NULL)
		factory = new ItemFactory();
	return factory;
}

Item* ItemFactory::getObject(int i) 
{
	if (i > -1 && i < objects.size())
		return objects[i]->clone();
	return NULL;
}

Item* ItemFactory::getObject(std::string name)
{
	for (auto* i : objects)
	{
		if (i->getName()._Equal(name))
			return i->clone();
	}
	return NULL;
}

void ItemFactory::drawObjectAt(int ID, Rectangle pos)
{
	if (ID < 0 || ID >= objects.size())
		return;
	objects[ID]->drawAt(pos);
}

void ItemFactory::drawItemDescription(int ID, int x, int y)
{
	if (ID < 0 || ID >= objects.size())
		return;
	std::string description = getDescription(ID);
	Vector2 descriptionSize = textSize(description.c_str(), textStandardSize);
	Rectangle dest = { x, y, descriptionSize.x, descriptionSize.y };
	DrawRectangleRec(dest, BLUE);
	drawText(description.c_str(), x, y, textStandardSize, BLACK);
}

bool ItemFactory::isStacableItem(int ID)
{
	if (ID < 0 || ID >= objects.size())
		return false;
	return objects[ID]->isStacable();

}