#pragma once
#include "Scene.h"
#include "../../GameObjects/Items/Item.h"
#include "../../GameObjects/Items/Tool/ToolItem.h"
#include "../Elements/RectangleEnter.h"
#include "../Elements/Element.h"
#include <list>
#include <vector>
#include <iostream>

struct ItemProperty
{
	int ID = 0;
	SpriteController* sprite = NULL;
	///Dane Kazdego obiektu
	std::string name;
	Rectangle pos;
	ItemType type;
	///Od kolizji obiektu
	bool hasLinesCollider;
	int nPoints=0;
	Vector2* points;
	///Czy mo¿na stakowaæ przedmioty
	bool isStacable;
	int stackSize;
	///Czy item jest do u¿ywania
	bool isUsingItem;
	float useTime;
	///Czy item zadaje obrarzenia
	bool isDealingDamage;
	float damage;
	float invisibleFrame;
	///czy item niszczy bloki
	bool isDestoryAble;
	int power;
	ToolType destroyType = ToolType::NON;
	///Czy jest broni¹ daleko zasiêgow¹
	bool isRangeWeapon;
	float projectalRange;
	int numberOfProjectal;
	float projectalSpeed;

	ItemProperty();

	~ItemProperty();

	void clearData();

	void addPointToCollisions();

	void removePointToCollisions();

	void saveToJson(nlohmann::json &j);

	void setDataFrom(ItemProperty item);

	void reLoadTexture();
};



class ItemEdytor :
    public Scene
{
	ItemProperty item;

	std::list<Element*> elements;
	std::vector<ItemProperty*> items;
	Element* lastPressed = NULL;
public:
    ItemEdytor();

	~ItemEdytor();

	virtual void start();

	virtual void update(float deltaTime);

	void newItem();

	void removeItem();

	virtual void draw();
};

