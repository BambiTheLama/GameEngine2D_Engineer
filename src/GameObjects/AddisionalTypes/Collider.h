#pragma once
#include "raylib.h"
#include <vector>
#include "../GameObject.h"
/// <summary>
/// Typ wyliczeniowy okreslajacy typ kolizji
/// </summary>
enum class CollisionType
{
	Rec, Lines, Circle,NON
};
/// <summary>
/// Typ wyliczyniowy okreslajacy w jakie akcje wchodzi obiekt
/// </summary>
enum class CollisionsCheckType
{
	NON, HitAbleOnly, DestoryAbleOnly, All, EnumSize
};
class HitAble;
class DestroyAble;
/// <summary>
/// Klasa odpowiedzialna za kolizje obiektu
/// </summary>
class Collider
{
	std::list<GameObject*> objectsToIgnore;
	CollisionsCheckType type;
	ObjectType ignoreType = ObjectType::NON;
protected:
	/// <summary>
	/// Konstruktor kopiujace dane z obiektu
	/// </summary>
	/// <param name="col"></param>
	Collider(Collider& col);
public:
	/// <summary>
	/// Konstuktor domysliny 
	/// </summary>
	/// <param name="type"></param>
	Collider(CollisionsCheckType type=CollisionsCheckType::NON);
	/// <summary>
	/// Konstuktor wczytujace dane z pliku json
	/// </summary>
	/// <param name="j"></param>
	Collider(nlohmann::json j);
	/// <summary>
	/// Sprawdza kolizje miedzy drugim obiektem
	/// </summary>
	/// <param name="c">obiekt miedzy ktorym sprawdzamy kolizje</param>
	/// <param name="thisPos">przesuniecie tego obiektu</param>
	/// <param name="otherPos">przesuniecie obiektu z ktorym sprawdzamy kolizje</param>
	/// <returns></returns>
	virtual bool checkCollisionToObj(GameObject* thisObj, Collider* otherCollider,GameObject* otherObject);
	/// <summary>
	/// Sprawdza czy obiekt koliduje z czyms
	/// </summary>
	/// <returns></returns>
	bool isCollidingWithSomething();
	/// <summary>
	/// Rysuje kolizje obiektu
	/// </summary>
	/// <param name="obj"></param>
	virtual void draw(GameObject* obj){}
	/// <summary>
	/// Zwraca kolizje w formie prostokata
	/// </summary>
	/// <returns></returns>
	virtual Rectangle getCollisionPos() { return{ 0,0,0,0 }; }
	/// <summary>
	/// Zwraca ile jest lini kolizji
	/// </summary>
	/// <returns></returns>
	virtual int getHomManyLines() { return 0; }
	/// <summary>
	/// Zwraca wszystkie punky lini
	/// </summary>
	/// <returns></returns>
	virtual Vector2* getLines() { return NULL; }
	/// <summary>
	/// Zwraca promiec okregu
	/// </summary>
	/// <returns></returns>
	virtual int getRadius() { return 0; }
	/// <summary>
	/// Zwraca punkt okregu
	/// </summary>
	/// <returns></returns>
	virtual Vector2 getCirlcePoint() { return { 0,0 }; }
	/// <summary>
	/// Zwraca typ kolizji
	/// </summary>
	/// <returns></returns>
	virtual CollisionType getCollisionType() { return CollisionType::NON; }
	/// <summary>
	/// Aktualizuje obiekt i sprawdza sprawdza interakcje z obiektami
	/// </summary>
	/// <param name="deltaTime"></param>
	/// <param name="obj"></param>
	virtual void update(float deltaTime, GameObject* obj, Vector2 moveBy={0,0});
	/// <summary>
	/// Metoda odpoweidzialna na interkacje z obiektem mozliwym do udrzenia
	/// </summary>
	/// <param name="hit"></param>
	virtual void onCollisionHitable(HitAble* hit){}
	/// <summary>
	/// Metoda odpoweidzialna na interkacje z obiektem mozliwym do zniszczenia
	/// </summary>
	/// <param name="hit"></param>
	virtual void onCollisionDestroyAble(DestroyAble* dest){}
	/// <summary>
	/// Dodaje obiekt do ignorowania kolizji
	/// </summary>
	/// <param name="ignore"></param>
	void addObjToIgnore(GameObject* ignore);
	/// <summary>
	/// Usuwa obiekt z listy ignorowanych
	/// </summary>
	/// <param name="ignore"></param>
	void removeObjectToIgnore(GameObject* ignore);
	/// <summary>
	/// Czysci lsite ignorowanych obiektow
	/// </summary>
	void clearListToIgnore();

	void setIgnoreType(ObjectType type) { ignoreType = type; }
};
/// <summary>
/// Srpawdza czy obiek kolizuje z innymi
/// </summary>
/// <param name="obj"></param>
/// <returns></returns>
bool checkCollision(GameObject* obj);
/// <summary>
/// Struktora odpowiedzialna za opisania prostej 
/// </summary>
struct LineData {
	float x1, x2, y1, y2;
	float a, b;
	/// <summary>
	/// Metoda obliczajaca wspolczyniki a i b prostej
	/// </summary>
	void calculateAB();
	/// <summary>
	/// Sprawdza czy linie przyzuja sie
	/// </summary>
	/// <param name="l">linia do porownania</param>
	/// <returns></returns>
	bool checkLines(LineData l);
};
/// <summary>
/// Sprawdza kolizje Prostokat z liniami
/// </summary>
/// <param name="points">tablica lini</param>
/// <param name="n">ilosc lini</param>
/// <param name="pos">Dane prostokatu</param>
/// <returns></returns>
bool checkCollision(Vector2* points, int n, Rectangle pos);
/// <summary>
/// Sprawdza kolizje dwoch zbiorow lini
/// </summary>
/// <param name="points">tablica lini 1</param>
/// <param name="n">ilosc lini 1</param>
/// <param name="points">tablica lini 2</param>
/// <param name="n">ilosc lini 2</param>
/// <returns></returns>
bool checkCollision(Vector2* points, int n, Vector2* points2, int n2);
/// <summary>
/// Liczy dystans z jednego punktu do drugiego
/// </summary>
/// <param name="x1"></param>
/// <param name="y1"></param>
/// <param name="x2"></param>
/// <param name="y2"></param>
/// <returns></returns>
float distance(float x1, float y1, float x2, float y2);
/// <summary>
/// Sprawdza kolizje miedzy linia a okregiem
/// </summary>
/// <param name="v">punk okregu</param>
/// <param name="radius">promien okregu</param>
/// <param name="p1">poczatek wspolzednych lini</param>
/// <param name="p2">koniec wspolzednych lini</param>
/// <returns></returns>
bool collideLineCircle(Vector2 v, float radius, Vector2 p1, Vector2 p2);
/// <summary>
/// Sprawdza kolizje okregu i zbioru lini 
/// </summary>
/// <param name="v">pozycja okregu</param> 
/// <param name="radius">promien okregu</param>
/// <param name="points">tablica punktow lini</param> 
/// <param name="n">ilosc lini</param>
/// <returns></returns>
bool collideLinesCircle(Vector2 v, float radius, Vector2* points, int n);