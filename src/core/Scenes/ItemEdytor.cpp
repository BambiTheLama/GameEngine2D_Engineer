#include "ItemEdytor.h"
#include "../../GameObjects/Items/StackItem.h"
#include "../../GameObjects/Items/Tool/ToolItem.h"
#include "../../GameObjects/Items/Weapon/Ammo.h"
#include "../../GameObjects/Items/Weapon/Bow.h"
#include "../Elements/LineColliderCheckBox.h"
#include "../Elements/CheckBoxOpenElements.h"
#include "../Elements/RectangleEnter.h"
#include "../Elements/VectorEnter.h"
#include "../Elements/FloatEnter.h"
#include "../Elements/TextEnter.h"
#include "../Elements/CheckBox.h"
#include "../Elements/IntEnter.h"
#include "../Elements/Add.h"
#include "../Elements/Remove.h"
#include "../Elements/EnumEnter.h"
#include "../Elements/AddItem.h"
#include "../Elements/RemoveItem.h"
#include <fstream>



ItemEdytor::ItemEdytor()
{
	item = new ItemProperty();
	//Odczyt danych z pliku json
	nlohmann::json j;
	std::ifstream reader;
	reader.open("Items.json");
	if (reader.is_open())
	{
		reader >> j;
		
	}
	reader.close();
	for(int i=0;i<j.size();i++)
	{
		ItemProperty* itemProp = new ItemProperty(j, i);
		itemProp->reLoadTexture();
		items.push_back(itemProp);
	}
	//Dodanie wszystkich przyciskow

	elements.push_back(new TextEnter({ 0,0,300,64 },"Name", &item->name));
	Rectangle pos = { 5,100,200,32 };
	std::string names[7] = { "has lines collider", "Is stacable" ,"is using item",
		"is dealing damage","is destory able","Is range weapon","IsAnimated"};
	bool* bPointers[7] = { &item->hasLinesCollider ,&item->isStacable, &item->isUsingItem,
		&item->isDealingDamage, &item->isDestoryAble,&item->isRangeWeapon,&item->animated };
	CheckBoxOpenElements* checkBoxs[7];
	checkBoxs[0] = new LineColliderCheckBox(pos, names[0], bPointers[0],item);
	pos.y += 48;
	for (int i = 1; i < 6; i++)
	{
		checkBoxs[i] = new CheckBoxOpenElements(pos, names[i], bPointers[i]);
		pos.y += 48;
	}
	checkBoxs[6] = new CheckBoxOpenElements(pos, names[6], bPointers[6],false);
	RectangleEnter* recEnter = new RectangleEnter({ 0,100,400,64 }, "Pos:", &item->pos);
	elements.push_back(recEnter);
	elements.push_back(checkBoxs[0]);
	checkBoxs[0]->setElementAbrow(recEnter);
	checkBoxs[0]->setElementBellow(checkBoxs[1]);
	first = checkBoxs[0];
	for (int i = 1; i < 6; i++)
	{
		checkBoxs[i]->setElementAbrow(checkBoxs[i - 1]);
		checkBoxs[i]->setElementBellow(checkBoxs[i + 1]);
		elements.push_back(checkBoxs[i]);
	}
	checkBoxs[6]->setElementAbrow(checkBoxs[5]);
	elements.push_back(checkBoxs[6]);
	float h = 32;
	////////////////////////////////////////////////////////////////////////////////////
	Element* e = new IntEnter({ 0,0,200,h }, "How Many Points: ", &item->nPoints);
	checkBoxs[0]->addElement(e);
	////////////////////////////////////////////////////////////////////////////////////
	e = new IntEnter({ 0,0,200,h }, "StackSize: ", &item->stackSize);
	checkBoxs[1]->addElement(e);
	////////////////////////////////////////////////////////////////////////////////////
	e = new FloatEnter({ 500,500,200,h }, "UseTime: ", &item->useTime);
	checkBoxs[2]->addElement(e);
	////////////////////////////////////////////////////////////////////////////////////
	e = new FloatEnter({ 0,0,200,h }, "Damage: ", &item->damage);
	checkBoxs[3]->addElement(e);
	e = new FloatEnter({ 00,00,200,h }, "Invisible Frames: ", &item->invisibleFrame);
	checkBoxs[3]->addElement(e);
	////////////////////////////////////////////////////////////////////////////////////
	e = new IntEnter({ 0,0,200,h }, "Power: ", &item->power);
	checkBoxs[4]->addElement(e);
	e = new EnumEnter({ 0,0,200,h }, "DestroyType: ", &item->destroyType, (int)ToolType::EnumSize, toolTypeDescription());
	checkBoxs[4]->addElement(e);
	////////////////////////////////////////////////////////////////////////////////////
	e = new FloatEnter({ 00,00,200,h }, "Projectal Range: ", &item->projectalRange);
	checkBoxs[5]->addElement(e);
	e = new IntEnter({ 0,0,200,h }, "Number Of Projectal: ", &item->numberOfProjectal);
	checkBoxs[5]->addElement(e);
	e = new FloatEnter({ 00,00,200,h }, "Projectal Speed:", &item->projectalSpeed);
	checkBoxs[5]->addElement(e);
	e = new EnumEnter({ 0,0,200,h }, "AmmoType: ", &item->ammoType, (int)AmmoType::EnumSize, ammoTypeDescription());
	checkBoxs[5]->addElement(e);
	//////////////////////////////////////////////////////////////////////////////////////
	e = new IntEnter({ 0,0,200,h }, "Frame: ", &item->frame);
	checkBoxs[6]->addElement(e);
	////////////////////////////////////////////////////////////////////////////////////
	Rectangle buttons = itemsSelect;
	buttons.y = 85;
	buttons.width = 64;
	buttons.height = 64;
	elements.push_back(new Remove(buttons, &firstItem));
	buttons.x += 80;
	elements.push_back(new Add(buttons, &firstItem));
	buttons.x += 80;
	elements.push_back(new AddItem(buttons, this));
	buttons.x += 80;
	elements.push_back(new RemoveItem(buttons, this));
	buttons.x += 80;
	elements.push_back(new EnumEnter({400,0,150,32},"ItemType:",&item->itemClass,(int)ItemClass::EnumSize, itemClassDescription()));
	if (items.size() > 0)
	{
		item->setDataFrom(*items[0]);
	}

	else
	{
		items.push_back(new ItemProperty());
		item->setDataFrom(*items[0]);
	}

}

ItemEdytor::~ItemEdytor()
{
	loadNewItem(0);
	nlohmann::json j;
	for (auto i : items)
	{
		i->saveToJson(j);
		delete i;
	}
	items.clear();
	std::ofstream writer;
	std::cout << j.dump(2) << std::endl;
	writer.open("Items.json");
	writer << j.dump(2) << std::endl;
	writer.close();
	for (Element* e : elements)
		delete e;

	elements.clear();
	delete item;
}

void ItemEdytor::start()
{
	for (auto* e : elements)
		e->updatePos();
	item->reLoadTexture();
}

void ItemEdytor::update(float deltaTime)
{
	int itemClass = item->itemClass;
	for (Element* e : elements)
		e->update();
	if (itemClass != item->itemClass)
	{
		item->update();
		first->updatePos();
	}

	checkPress();
	
}

void ItemEdytor::newItem()
{
	ItemProperty *i = new ItemProperty();
	i->clearData();
	i->ID = items.size();
	items.push_back(i);
}

void ItemEdytor::removeItem()
{
	int ID = item->ID;
	if (ID >= 0 && ID < items.size())
	{
		if (items[ID])
		{
			delete items[ID];
			items[ID] = NULL;
		}
		for (int i = ID; i < items.size()-1; i++)
		{
			items[i] = items[i + 1];
			items[i]->ID = i;
		}
		items.pop_back();
		if (ID < items.size())
			item->setDataFrom(*items[ID]);
		else if (items.size() > 0)
			item->setDataFrom(*items[items.size() - 1]);
		else
			addItem();
	}
}

void ItemEdytor::popBackItem()
{
	if (items.size() <= 0)
		return;
	delete items[items.size() - 1];
	items.pop_back();
}
void ItemEdytor::addItem()
{
	items.push_back(new ItemProperty());
	items[items.size() - 1]->ID = items.size() - 1;
}

void ItemEdytor::draw()
{


	itemDrawShow();
	int n = items.size() - firstItem;

	const int size = 64;
	int howManyElementsInRow = getHowManyElementsInTheRow();

	if (n > howManyElementsInRow * 7)
		n = howManyElementsInRow * 7;
	
	for (int i = 0; i < n; i++)
		items[i+firstItem]->draw(itemPos(i));
	std::list<Element*>::iterator it = elements.end();
	do {
		it--;
		(*it)->draw();
	} while (*it != *elements.begin());

}
Rectangle ItemEdytor::itemPos(int i)
{
	const int size = 64;
	int howManyElementsInRow = getHowManyElementsInTheRow();
	int x = i % howManyElementsInRow;
	int y = i / howManyElementsInRow;
	return { itemsSelect.x + x * size * 1.25f,itemsSelect.y + y * size * 1.25f,size,size };
}

void ItemEdytor::lastElementPressed()
{
	if (!lastPressed)
		return;
	
	lastPressed->unPress();
	lastPressed = NULL;
	if (!item->checkTexture())
	{
		item->reLoadTexture();
	}

}
void ItemEdytor::checkPress()
{
	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		lastElementPressed();

		for (Element* e : elements)
		{
			if (e->press())
			{
				lastPressed = e;
				break;
			}
		}
		if (!lastPressed)
		{
			itemDrawPointsClick();
			itemsSelectPointClick();
		}

	}
	else if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
	{
		itemDrawPointsHold();
	}
	else if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
	{
		holdPoint = -1;	
	}

}

void ItemEdytor::itemsSelectPointClick()
{
	if (!CheckCollisionPointRec(GetMousePosition(), itemsSelect))
		return;
	int n = items.size() - firstItem;

	for (int i = 0; i < n; i++)
		if (CheckCollisionPointRec(GetMousePosition(), itemPos(i)))
		{
			loadNewItem(i + firstItem);
		}
}
void ItemEdytor::itemDrawPointsClick()
{
	if (!CheckCollisionPointRec(GetMousePosition(), itemDraw))
		return;
	
	Rectangle pos = itemDraw;
	for (int i = 0; i < item->nPoints; i++)
	{
		Vector2 p = item->points[i];
		p.x *= pos.width / item->pos.width;
		p.y *= pos.height / item->pos.height;
		p.x += pos.x;
		p.y += pos.y;
		if (CheckCollisionPointCircle(GetMousePosition(), p, 7))
		{

			holdPoint = i;
		}
	}
	
}
void ItemEdytor::itemDrawPointsHold()
{
	if (CheckCollisionPointRec(GetMousePosition(), itemDraw))
	{
		if (holdPoint >= 0 && holdPoint < item->nPoints)
		{
			Rectangle pos = itemDraw;
			Vector2 p = GetMousePosition();
			p.x -= pos.x;
			p.y -= pos.y;
			p.x *= item->pos.width / pos.width;
			p.y *= item->pos.height / pos.height;
			item->points[holdPoint] = p;
		}
		else
			holdPoint = -1;
	}
}
void ItemEdytor::itemDrawShow()
{
	if (!item->sprite)
		return;
	
	Rectangle pos = itemDraw;
	int w = item->pos.width / 16;
	int h = item->pos.height / 16;
	int sizeW = pos.width / w;
	int sizeH = pos.height / h;
	for (int x = 0; x < w; x++)
		for (int y = 0; y < h; y++)
			DrawRectangle(pos.x + x * sizeW, pos.y + y * sizeH, sizeW, sizeH, x % 2 == y % 2 ? GRAY : WHITE);
	drawText(TextFormat("{0,0}"), pos.x, pos.y, textStandardSize, BLACK);
	drawText(TextFormat("{%d,0}", (int)item->pos.width), pos.x + pos.width, pos.y, textStandardSize, BLACK);
	drawText(TextFormat("{%d,%d}", (int)item->pos.width, (int)item->pos.height), pos.x + pos.width, pos.y + pos.height, textStandardSize, BLACK);
	drawText(TextFormat("{0,%d}", (int)item->pos.height), pos.x, pos.y + pos.height, textStandardSize, BLACK);

	drawText(TextFormat("{%d,0}", (int)item->pos.width / 2), pos.x + pos.width / 2, pos.y, textStandardSize, BLACK);

	drawText(TextFormat("{%d,%d}", (int)item->pos.width / 2, (int)item->pos.height), pos.x + pos.width / 2, pos.y + pos.height, textStandardSize, BLACK);

	drawText(TextFormat("{0,%d}", (int)item->pos.height / 2), pos.x, pos.y + pos.height / 2, textStandardSize, BLACK);
	drawText(TextFormat("{%d,%d}", (int)item->pos.width, (int)item->pos.height / 2), pos.x + pos.width, pos.y + pos.height / 2, textStandardSize, BLACK);

	DrawRectangleLinesEx({ pos.x - 3,pos.y - 3,pos.width + 6,pos.height + 6 }, 3, BLACK);
	if(item->animated)
		item->sprite->draw(pos,item->frame);
	else
		item->sprite->draw(pos);
	DrawTextWithOutline(TextFormat("%d", item->ID), pos.x-32, pos.y-32, textStandardSize, WHITE, BLACK);
	if (!item->points)
		return;

	
	for (int i = 0; i < item->nPoints; i++)
	{
		Vector2 p = item->points[i];
		p.x *= pos.width / item->pos.width;
		p.y *= pos.height / item->pos.height;
		p.x += pos.x;
		p.y += pos.y;
		Vector2 p2 = item->points[(i + 1) % item->nPoints];
		p2.x *= pos.width / item->pos.width;
		p2.y *= pos.height / item->pos.height;
		p2.x += pos.x;
		p2.y += pos.y;
		DrawLineEx(p, p2, 4, WHITE);
		DrawLineEx(p, p2, 2, BLACK);
	}
	for (int i = 0; i < item->nPoints; i++)
	{
		Vector2 p = item->points[i];
		p.x *= pos.width / item->pos.width;
		p.y *= pos.height / item->pos.height;
		p.x += pos.x;
		p.y += pos.y;
		DrawCircleV(p, 7, holdPoint == i ? GREEN : RED);
		DrawTextWithOutline(TextFormat("%d", i), p.x, p.y, textStandardSize, BLACK, WHITE);
	}


}

void ItemEdytor::loadNewItem(int i)
{
	if (item->ID < items.size() && item->ID >= 0)
		items[item->ID]->setDataFrom(*item);
	item->setDataFrom(*items[i]);
	item->update();
	for (auto e : elements)
		e->reloadData();
	first->updatePos();
}

int ItemEdytor::getHowManyElementsInTheRow()
{
	const int size = 64;
	int howManyElementsInRow = itemsSelect.width / size;
	if (howManyElementsInRow <= 0)
		howManyElementsInRow = 1;
	return howManyElementsInRow;
}