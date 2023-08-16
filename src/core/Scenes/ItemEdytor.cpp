#include "ItemEdytor.h"
#include "../../GameObjects/Items/StackItem.h"
#include "../../GameObjects/Items/Tool/ToolItem.h"
#include "../../GameObjects/Items/Weapon/Ammo.h"
#include "../../GameObjects/Items/Weapon/Bow.h"
#include "../Elements/CheckBoxOpenElements.h"
#include "../Elements/RectangleEnter.h"
#include "../Elements/FloatEnter.h"
#include "../Elements/TextEnter.h"
#include "../Elements/CheckBox.h"
#include "../Elements/IntEnter.h"
#include <fstream>



ItemEdytor::ItemEdytor()
{
	//Odczyt danych z pliku json
	nlohmann::json j;
	std::ifstream reader;
	reader.open("Items.json");
	if (reader.is_open())
	{
		reader >> j;
		
	}
	std::cout << j.dump(2)<<std::endl;
	reader.close();
	for(int i=0;i<j.size();i++)
	{
		items.push_back(new ItemProperty(j, i));
	}

	item =ItemProperty(j, 0);
	//Dodanie wszystkich przyciskow

	elements.push_back(new TextEnter({ 0,0,300,64 },"Name", &item.name));
	Rectangle pos = { 0,100,200,32 };
	std::string names[6] = { "has lines collider", "Is stacable" ,"is using item",
		"is dealing damage","is destory able","Is range weapon"};
	bool* bPointers[6] = { &item.hasLinesCollider ,&item.isStacable, &item.isUsingItem,
		&item.isDealingDamage, &item.isDestoryAble,&item.isRangeWeapon };
	CheckBoxOpenElements* checkBoxs[6];
	for (int i = 0; i < 6; i++)
	{
		checkBoxs[i] = new CheckBoxOpenElements(pos, names[i], bPointers[i]);
		pos.y += 48;
	}
	RectangleEnter* recEnter = new RectangleEnter({ 0,100,500,64 }, "Pos:", &item.pos);
	elements.push_back(recEnter);
	elements.push_back(checkBoxs[0]);
	checkBoxs[0]->setElementAbrow(recEnter);
	checkBoxs[0]->setElementBellow(checkBoxs[1]);
	for (int i = 1; i < 5; i++)
	{
		checkBoxs[i]->setElementAbrow(checkBoxs[i - 1]);
		checkBoxs[i]->setElementBellow(checkBoxs[i + 1]);
		elements.push_back(checkBoxs[i]);
	}
	checkBoxs[5]->setElementAbrow(checkBoxs[4]);
	elements.push_back(checkBoxs[5]);
	float h = 32;
	Element* e = new IntEnter({ 0,0,200,h }, "How Many Points: ", &item.nPoints);
	checkBoxs[0]->addElement(e);

	e = new IntEnter({ 0,0,200,h }, "StackSize: ", &item.stackSize);
	checkBoxs[1]->addElement(e);

	e = new FloatEnter({ 500,500,200,h }, "UseTime: ", &item.useTime);
	checkBoxs[2]->addElement(e);

	e = new FloatEnter({ 0,0,200,h }, "Damage: ", &item.damage);
	checkBoxs[3]->addElement(e);
	e = new FloatEnter({ 00,00,200,h }, "Invisible Frames: ", &item.invisibleFrame);
	checkBoxs[3]->addElement(e);

	e = new IntEnter({ 0,0,200,h }, "Power: ", &item.power);
	checkBoxs[4]->addElement(e);


	e = new FloatEnter({ 00,00,200,h }, "Projectal Range: ", &item.projectalRange);
	checkBoxs[5]->addElement(e);
	e = new IntEnter({ 0,0,200,h }, "Number Of Projectal: ", &item.numberOfProjectal);
	checkBoxs[5]->addElement(e);
	e = new FloatEnter({ 00,00,200,h }, "Projectal Speed:", &item.projectalSpeed);
	checkBoxs[5]->addElement(e);
}

ItemEdytor::~ItemEdytor()
{

	nlohmann::json j;
	for (auto i : items)
	{
		i->saveToJson(j);
	}

	std::cout << j.dump(2);
	std::ofstream writer;
	writer.open("Items.json");
	writer << j.dump(2)<<std::endl;
	writer.close();

	for (Element* e : elements)
		delete e;

	elements.clear();
}

void ItemEdytor::start()
{
	for (auto* e : elements)
		e->updatePos();

}

void ItemEdytor::update(float deltaTime)
{
	for (Element* e : elements)
		e->update();
	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		if (lastPressed != NULL)
		{
			lastPressed->unPress();
			lastPressed = NULL;
		}
		for (Element* e : elements)
		{
			if (e->press())
			{
				lastPressed = e;
				break;
			}
			
		}
			
	}
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
	if (item.ID >= 0 && item.ID < items.size())
	{
		if (items[item.ID] != NULL)
		{
			delete items[item.ID];
			items[item.ID] = NULL;
		}
	}
}

void ItemEdytor::draw()
{
	for (Element* e : elements)
		e->draw();
}