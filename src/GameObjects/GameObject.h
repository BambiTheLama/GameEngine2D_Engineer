#pragma once
#include "raylib.h"
#include <math.h>
#include "../core/Controllers/AnimationController.h"

float cursorTarget(Vector2 objPos);
float degreeToRadius(float degree);
float radiusToDegree(float degree);
Vector2 deltaFromDegree(float degree,float speed=1);

/// <summary>
/// Enum okreœlaj¹cy do jakiego typu nale¿y dany obiekt
/// </summary>
enum class ObjectType
{
	NPC, Item, Block, Particle, Player, NON, Projectal, Plant
};
class Factory;
class BlockFactory;
/// <summary>
/// Klasa bazowa dla wszystkich obiektów gry
/// </summary>
class GameObject
{

	unsigned int ID = 0;
protected:
	Rectangle pos;
	std::string name;
	GameObject(GameObject& obj);
public:
	GameObject(Rectangle pos,std::string name);
	/// <summary>
	/// Wiztualny destruktor by by³ wywo³any odpowiedni z klas dziedzicz¹cych
	/// </summary>
	virtual ~GameObject();
	/// <summary>
	/// Metoda aktywowana przy starcie sceny gdy wszystkie obiekty siê wygeneruj¹
	/// </summary>
	virtual void start(){}
	/// <summary>
	/// Metoda aktualizuj¹ca obiekt
	/// </summary>
	virtual void update()=0;
	/// <summary>
	/// Metoda do rysowania obiektu
	/// </summary>
	virtual void draw()=0;
	/// <summary>
	/// Metoda get definiuj¹ca jakiego typu jest obiekt
	/// </summary>
	/// <returns></returns>
	virtual ObjectType getType() = 0;
	/// <summary>
	/// Ustawienie nowego punktu x i y obiektu
	/// </summary>
	/// <param name="movePos"></param>
	virtual void setMovePos(Vector2 movePos) { pos.x = movePos.x; pos.y = movePos.y; }
	/// <summary>
	/// Dodaje do pozycji wartosc przemieszczenia
	/// </summary>
	/// <param name="toAdd">Przemieszczenie</param>
	virtual void addToPos(Vector2 toAdd) { pos.x += toAdd.x, pos.y += toAdd.y; }
	/// <summary>
	/// Metoda zwraca pozycje obiektu
	/// </summary>
	/// <returns>Pozycja obiektu</returns>
	virtual Rectangle getPos() { return pos; }
	/// <summary>
	/// Metoda do klonowania obiektu
	/// </summary>
	/// <returns>Klon obiektu</returns>
	virtual GameObject* clone() = 0;
	/// <summary>
	/// Czy obiekt wchodzi w kolizjê z innymi
	/// </summary>
	/// <returns></returns>
	virtual bool isColliding() { return false; }
	/// <summary>
	/// Czy obiekt mo¿e siê poruszaæ 
	/// </summary>
	/// <param name="canMove"></param>
	virtual void setCanMoveObject(bool canMove){}
	/// <summary>
	/// Zwraca ID dla obiektu ka¿dy typ obiektów ma w³asne ID
	/// </summary>
	/// <returns>ID obiektu</returns>
	unsigned int getID() { return ID; }

	friend class Factory;
	friend class BlockFactory;
	friend class ItemFactory;
};

bool checkCollision(GameObject* obj);