#include "ItemEdytor.h"
#include "../../GameObjects/Items/StackItem.h"
#include "../../GameObjects/Items/Tool/ToolItem.h"
#include "../../GameObjects/Items/Weapon/Ammo.h"
#include "../../GameObjects/Items/Weapon/Bow.h"
#include "../../json.hpp"
#include "../Elements/TextEnter.h"
#include "../Elements/CheckBox.h"
#include <fstream>

ItemProperty::ItemProperty()
{

}

ItemProperty::~ItemProperty()
{
	if(sprite!=NULL)
		delete sprite;
}
void ItemProperty::clearData()
{

	sprite = NULL;
	name="";
	pos={0,0,0,0};

	type=ItemType::Normal;
	///Od kolizji obiektu
	hasLinesCollider=false;
	nPoints = 0;
	if (points != NULL)
		delete points;
	points=NULL;
	///Czy mo¿na stakowaæ przedmioty
	isStacable=false;
	stackSize=0;
	///Czy item jest do u¿ywania
	isUsingItem=false;
	useTime=0;
	///Czy item zadaje obrarzenia
	isDealingDamage=false;
	damage=0;
	invisibleFrame=0;
	///czy item niszczy bloki
	isDestoryAble=false;
	power=0;
	destroyType=ToolType::NON;
	///Czy jest broni¹ daleko zasiêgow¹
	isRangeWeapon=false;
	projectalRange=0;
	numberOfProjectal=0;
	projectalSpeed=0;
}

void ItemProperty::addPointToCollisions()
{
	if (nPoints <= 0)
	{
		nPoints = 1;
		points = new Vector2[1];
		points[0] = { 0,0 };
	}
	else
	{
		nPoints++;
		Vector2 *points= new Vector2[nPoints];
		for (int i = 0; i < nPoints - 1; i++)
			points[i] = this->points[i];
		points[nPoints - 1] = { 0,0 };
		delete this->points;
		this->points = points;
	}
}

void ItemProperty::removePointToCollisions()
{
	if (nPoints <= 0)
	{
		nPoints = 0;
		points = NULL;
	}
	else
	{
		nPoints--;
		if (nPoints <= 0)
		{
			delete points;
			points = NULL;
			return;
		}
		Vector2* points = new Vector2[nPoints];
		for (int i = 0; i < nPoints; i++)
			points[i] = this->points[i];
		delete this->points;
		this->points = points;
	}
}

void ItemProperty::saveToJson(nlohmann::json &j)
{
	j[ID]["Name"] = name;
	j[ID]["Pos"] = { pos.x,pos.y,pos.width,pos.height };
	j[ID]["Type"] = type;
	if (hasLinesCollider)
	{
		j[ID]["LineCollsionN"] = nPoints;
		for (int i = 0; i < nPoints; i++)
			j[ID]["Point" + std::to_string(i)] = { points[i].x,points[i].y };
	}
	if (isStacable)
	{
		j[ID]["StackSize"] = stackSize;
	}
	if (isUsingItem)
	{
		j[ID]["UseTime"] = useTime;
	}
	if (isDealingDamage)
	{
		j[ID]["Damage"] = damage;
		j[ID]["InvisibleFrame"] = invisibleFrame;
	}
	if (isDestoryAble)
	{
		j[ID]["Power"] = power;
		j[ID]["DestoryType"] = destroyType;
	}
	if (isRangeWeapon)
	{
		j[ID]["Range"] = projectalRange;
		j[ID]["Projectals"] = numberOfProjectal;
		j[ID]["Speed"] = projectalSpeed;
	}
}

void ItemProperty::setDataFrom(ItemProperty item)
{
	ID = item.ID;
	name = item.name;
	pos = item.pos;
	type = item.type;
	///Od kolizji obiektu
	hasLinesCollider = item.hasLinesCollider;
	nPoints = item.nPoints;
	if (item.points != NULL)
	{
		points = new Vector2[nPoints];
		for (int i = 0; i < nPoints; i++)
			points[i] = item.points[i];
	}
	///Czy mo¿na stakowaæ przedmioty
	isStacable = item.isStacable;
	stackSize = item.stackSize;
	///Czy item jest do u¿ywania
	isUsingItem = item.isUsingItem;
	useTime = item.useTime;
	///Czy item zadaje obrarzenia
	isDealingDamage = item.isDealingDamage;
	damage = item.damage;
	invisibleFrame = item.invisibleFrame;
	///czy item niszczy bloki
	isDestoryAble = item.isDestoryAble;
	power = item.power;
	destroyType = item.destroyType;
	///Czy jest broni¹ daleko zasiêgow¹
	isRangeWeapon = item.isRangeWeapon;
	projectalRange = item.projectalRange;
	numberOfProjectal = item.numberOfProjectal;
	projectalSpeed = item.projectalSpeed;
}

void ItemProperty::reLoadTexture()
{
	if (sprite != NULL)
	{
		delete sprite;
	}
	std::string path = "Resource/Items/" + name + ".png";
	sprite = new SpriteController(path.c_str());
}

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
	reader.close();
	//Dodanie wszystkich przyciskow
	item.clearData();
	elements.push_back(new TextEnter({ 0,0,300,64 },"Name", &item.name));
	Rectangle pos = { 0,100,200,32 };
	std::string names[6] = { "has lines collider", "Is stacable" ,"is using item",
		"is dealing damage","is destory able","Is range weapon"};
	bool* bPointers[6] = { &item.hasLinesCollider ,&item.isStacable, &item.isUsingItem,
		&item.isDealingDamage, &item.isDestoryAble,&item.isRangeWeapon };
	for (int i = 0; i < 6; i++)
	{
		elements.push_back(new CheckBox(pos, names[i], bPointers[i]));
		pos.y += 48;
	}
}
ItemEdytor::~ItemEdytor()
{
	ItemProperty* i = new ItemProperty();
	i->setDataFrom(item);
	items.push_back(i);
	nlohmann::json j;
	for (auto i : items)
	{
		i->saveToJson(j);
		delete i;
	}

	std::cout << j.dump(2);
	std::ofstream writer;
	writer.open("Items.json");
	writer << j.dump(2);
	writer.close();

	for (Element* e : elements)
		delete e;

	elements.clear();
}
void ItemEdytor::start()
{

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