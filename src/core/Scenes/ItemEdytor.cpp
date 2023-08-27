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
	checkBoxs[0] = new LineColliderCheckBox(pos, names[0], bPointers[0],&item);
	pos.y += 48;
	for (int i = 1; i < 6; i++)
	{
		checkBoxs[i] = new CheckBoxOpenElements(pos, names[i], bPointers[i]);
		pos.y += 48;
	}
	RectangleEnter* recEnter = new RectangleEnter({ 0,100,400,64 }, "Pos:", &item.pos);
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
	if (items.size() <= 0)
		items.push_back(new ItemProperty());
	//items[0]->setDataFrom(item);
}

ItemEdytor::~ItemEdytor()
{


	nlohmann::json j;
	for (auto i : items)
	{
		i->saveToJson(j);
		delete i;
	}
	items.clear();
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
	item.reLoadTexture();
}

void ItemEdytor::update(float deltaTime)
{
	for (Element* e : elements)
		e->update();
	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		if (lastPressed)
		{
			lastPressed->unPress();
			lastPressed = NULL;
			if (item.sprite == NULL)
				item.reLoadTexture();
			else
			{
				if (!item.sprite->getPath().find(item.name + ".png"));
				item.reLoadTexture();
			}
		}
		
		for (Element* e : elements)
		{
			if (e->press())
			{
				lastPressed = e;
				break;
			}
		}
		if (lastPressed == NULL)
		{
			if (CheckCollisionPointRec(GetMousePosition(), itemDraw))
			{
				Rectangle pos = itemDraw;
				for (int i = 0; i < item.nPoints; i++)
				{
					Vector2 p = item.points[i];
					p.x *= pos.width / item.pos.width;
					p.y *= pos.height / item.pos.height;
					p.x += pos.x;
					p.y += pos.y;
					if (CheckCollisionPointCircle(GetMousePosition(), p, 7))
					{
						holdPoint = i;
					}
				}
			}
		}
	}
	if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
	{
		if (CheckCollisionPointRec(GetMousePosition(), itemDraw))
		{
			if (holdPoint >= 0 && holdPoint < item.nPoints)
			{
				Rectangle pos = itemDraw;
				Vector2 p = GetMousePosition();
				p.x -= pos.x;
				p.y -= pos.y;
				p.x *= item.pos.width / pos.width;
				p.y *= item.pos.height / pos.height;
				item.points[holdPoint] = p;
			}
			else
				holdPoint = -1;
		}

	}
	if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
	{
		holdPoint = -1;
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
		if (items[item.ID])
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
	if (item.sprite)
	{
		Rectangle pos = itemDraw;
		int w = item.pos.width / 16;
		int h = item.pos.height / 16;
		int sizeW = pos.width / w;
		int sizeH = pos.height / h;
		for (int x = 0; x < w; x++)
			for (int y = 0; y < h; y++)
				DrawRectangle(pos.x + x * sizeW, pos.y + y * sizeH, sizeW, sizeH, x % 2 == y % 2 ? GRAY : WHITE);
		drawText(TextFormat("{0,0}"), pos.x, pos.y, textStandardSize, BLACK);
		drawText(TextFormat("{%d,0}",(int)item.pos.width), pos.x+pos.width, pos.y, textStandardSize, BLACK);
		drawText(TextFormat("{%d,%d}", (int)item.pos.width, (int)item.pos.height), pos.x + pos.width, pos.y + pos.height, textStandardSize, BLACK);
		drawText(TextFormat("{0,%d}", (int) item.pos.height), pos.x, pos.y + pos.height, textStandardSize, BLACK);

		drawText(TextFormat("{%d,0}", (int)item.pos.width / 2), pos.x + pos.width/2, pos.y, textStandardSize, BLACK);

		drawText(TextFormat("{%d,%d}", (int)item.pos.width/2, (int)item.pos.height), pos.x + pos.width/2, pos.y + pos.height, textStandardSize, BLACK);

		drawText(TextFormat("{0,%d}", (int)item.pos.height/2), pos.x , pos.y + pos.height/2, textStandardSize, BLACK);
		drawText(TextFormat("{%d,%d}", (int)item.pos.width, (int)item.pos.height/2), pos.x + pos.width, pos.y + pos.height/2, textStandardSize, BLACK);

		DrawRectangleLinesEx({ pos.x - 3,pos.y - 3,pos.width + 6,pos.height + 6 }, 3, BLACK);	
		item.sprite->draw(pos);
		for (int i = 0; i < item.nPoints; i++)
		{
			Vector2 p = item.points[i];
			p.x *= pos.width / item.pos.width;
			p.y *= pos.height / item.pos.height;
			p.x += pos.x;
			p.y += pos.y;
			Vector2 p2 = item.points[(i+1)%item.nPoints];
			p2.x *= pos.width / item.pos.width;
			p2.y *= pos.height / item.pos.height;
			p2.x += pos.x;
			p2.y += pos.y;
			DrawLineEx(p, p2, 4, WHITE);
			DrawLineEx(p, p2, 2, BLACK);
		}
		for (int i = 0; i < item.nPoints; i++)
		{
			Vector2 p = item.points[i];
			p.x *= pos.width / item.pos.width;
			p.y *= pos.height / item.pos.height;
			p.x += pos.x;
			p.y += pos.y;
			DrawCircleV(p, 7, holdPoint==i?GREEN:RED);
			DrawTextWithOutline(TextFormat("%d", i), p.x, p.y, textStandardSize, BLACK,WHITE);
		}

	}

}