#pragma once
#include "raylib.h"
#include "../../Controllers/SpriteController.h"
#include "../../../GameObjects/Items/Tool/ToolItem.h"
#include "../../../json.hpp"
#include <list>
#include <vector>
#include <iostream>

enum class ItemClass
{
	StackItem,
	ToolItem,
	Bow,
	Ammo,
};

struct ItemProperty
{

	int ID = 0;
	SpriteController* sprite = NULL;
	///Dane Kazdego obiektu
	ItemClass itemClass=ItemClass::StackItem;
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
	ToolType destroyType = ToolType::NON;
	///Czy jest broni¹ daleko zasiêgow¹
	bool isRangeWeapon;
	float projectalRange;
	int numberOfProjectal;
	float projectalSpeed;

	ItemProperty();

	ItemProperty(nlohmann::json& j,int ID);

	~ItemProperty();

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
