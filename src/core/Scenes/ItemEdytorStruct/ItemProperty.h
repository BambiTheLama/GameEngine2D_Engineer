#pragma once
#include "raylib.h"
#include "../../Controllers/SpriteController.h"
#include "../../../GameObjects/Items/Tool/ToolItem.h"
#include "json.hpp"
#include "../../../GameObjects/Items/Weapon/Ammo.h"
#include <list>
#include <vector>
#include <iostream>

enum class ItemClass
{
	StackItem,
	ToolItem,
	Bow,
	Ammo,


	EnumSize
};

std::string itemClassDescription();

struct ItemProperty
{

	int ID = 0;
	SpriteController* sprite = NULL;
	bool animated = false;
	int frame = 0;
	///Dane Kazdego obiektu
	int itemClass=(int)ItemClass::StackItem;
	std::string name;
	Rectangle pos;
	///Od kolizji obiektu
	bool hasLinesCollider;
	int nPoints = 0;
	Vector2* points=NULL;
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
	int destroyType = (int)ToolType::NON;
	///Czy jest broni¹ daleko zasiêgow¹
	bool isRangeWeapon;
	int ammoType=(int)AmmoType::Arrow;
	float projectalRange;
	int numberOfProjectal;
	float projectalSpeed;

	ItemProperty();

	ItemProperty(nlohmann::json& j,int ID);

	~ItemProperty();

	void update();

	void clearData();

	void updatePointsToCollisions();

	void addPointToCollisions();

	void removePointToCollisions();

	void saveToJson(nlohmann::json& j);

	void setDataFrom(ItemProperty& item);

	void reLoadTexture();

	void draw(Rectangle pos);

	bool checkTexture();
private:
	int sizePointsBefore=0;
};
