#pragma once
#include "raylib.h"
#include "../../Controllers/SpriteController.h"
#include "../../../GameObjects/Items/Tool/ToolItem.h"
#include "json.hpp"
#include "../../../GameObjects/Items/Weapon/Ammo.h"
#include <list>
#include <vector>
#include <iostream>
/// <summary>
/// Typ wyliczeniowy okreslajacy klase obiektu
/// </summary>
enum class ItemClass
{
	StackItem,
	ToolItem,
	Bow,
	Ammo,
	PlaceItems,


	EnumSize
};
/// <summary>
/// Zwraca opis klass z enuma ItemClass
/// </summary>
/// <returns></returns>
std::string itemClassDescription();
/// <summary>
/// Struktura okreslajaca dane obiektu
/// </summary>
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
	///Czy powoduje pojawienie siê obiektów na scenie
	bool isSpawnObject;
	int spawnObjectID;
	///Wartosc itemu
	bool isValue;
	int value;
	/// <summary>
	/// Konstruktor domyslny obiketu 
	/// </summary>
	ItemProperty();
	/// <summary>
	/// Konstuktor wczytujace dane z pliku typu json
	/// </summary>
	/// <param name="j">plik json</param>
	/// <param name="ID">Id obiektu</param>
	ItemProperty(nlohmann::json& j, int ID);
	/// <summary>
	/// Destukrot domyslny obiektu
	/// </summary>
	~ItemProperty();
	/// <summary>
	/// aktualizuje ktore pola sa aktywne a ktore nie na podstawie typu wyliczeniowego determinujacy klase obiektu
	/// </summary>
	void update();
	/// <summary>
	/// Czysci dane obiektu 
	/// </summary>
	void clearData();
	/// <summary>
	/// Aktualizuje punkty wchodzece w interkacje z innymi obiektami
	/// </summary>
	void updatePointsToCollisions();
	/// <summary>
	/// Dodaje nowy punkt do interakcji z okbiektami
	/// </summary>
	void addPointToCollisions();
	/// <summary>
	/// Usuwa punkt do interakcji z okbiektami
	/// </summary>
	void removePointToCollisions();
	/// <summary>
	/// Zapsiuje dane do pliku json
	/// </summary>
	/// <param name="j"></param>
	void saveToJson(nlohmann::json& j);
	/// <summary>
	/// Wczytuje dane z pliku json
	/// </summary>
	/// <param name="item"></param>
	void setDataFrom(ItemProperty& item);
	/// <summary>
	/// Wczytuje na nowo texture obiektu
	/// </summary>
	void reLoadTexture();
	/// <summary>
	/// Rysuje texture obiektu
	/// </summary>
	/// <param name="pos"></param>
	void draw(Rectangle pos);
	/// <summary>
	/// Sprawdza czy ospowiednia textura zostala zaladowana
	/// </summary>
	/// <returns></returns>
	bool checkTexture();
private:
	int sizePointsBefore=0;
};
