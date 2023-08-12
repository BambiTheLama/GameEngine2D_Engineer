#pragma once
#include "raylib.h"
#include <math.h>
#include "../core/Controllers/AnimationController.h"
#include "../core/Properties.h"

/// <summary>
/// Zwraca kat od obiektu do pozycji kursora
/// </summary>
/// <param name="objPos">Pozycja obiketu</param>
/// <returns>Kat padania</returns>
float cursorTarget(Vector2 objPos);
/// <summary>
/// Konwertuje stopnie na radiany
/// </summary>
/// <param name="degree"></param>
/// <returns></returns>
float degreeToRadius(float degree);
/// <summary>
/// Konwertuje radiany na stopnie
/// </summary>
/// <param name="degree"></param>
/// <returns></returns>
float radiusToDegree(float radius);
/// <summary>
/// Zwraca jak obiekt powinien si� porusza� xy z podan� pr�dko�ci� i k�tem
/// </summary>
/// <param name="degree"></param>
/// <param name="speed"></param>
/// <returns></returns>
Vector2 deltaFromDegree(float degree,float speed=1);

/// <summary>
/// Enum okre�laj�cy do jakiego typu nale�y dany obiekt
/// </summary>
enum class ObjectType
{
	NPC, Item, Block, Particle, Player, NON, Projectal, Plant
};
class Factory;
class BlockFactory;
/// <summary>
/// Klasa bazowa dla wszystkich obiekt�w gry
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
	/// Wiztualny destruktor by by� wywo�any odpowiedni z klas dziedzicz�cych
	/// </summary>
	virtual ~GameObject();
	/// <summary>
	/// Metoda aktywowana przy starcie sceny gdy wszystkie obiekty si� wygeneruj�
	/// </summary>
	virtual void start(){}
	/// <summary>
	/// Metoda aktualizuj�ca obiekt
	/// </summary>
	virtual void update()=0;
	/// <summary>
	/// Metoda do rysowania obiektu
	/// </summary>
	virtual void draw()=0;
	/// <summary>
	/// Metoda get definiuj�ca jakiego typu jest obiekt
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
	/// Czy obiekt wchodzi w kolizj� z innymi
	/// </summary>
	/// <returns></returns>
	virtual bool isColliding() { return false; }
	/// <summary>
	/// Czy obiekt mo�e si� porusza� 
	/// </summary>
	/// <param name="canMove"></param>
	virtual void setCanMoveObject(bool canMove){}
	/// <summary>
	/// Zwraca ID dla obiektu ka�dy typ obiekt�w ma w�asne ID
	/// </summary>
	/// <returns>ID obiektu</returns>
	unsigned int getID() { return ID; }
	/// <summary>
	/// Zwraca nazw� obiektu
	/// </summary>
	/// <returns>Nazwa obiektu</returns>
	std::string getName() { return name; }

	friend class Factory;
	friend class BlockFactory;
	friend class ItemFactory;
	friend class PlantsFactory;
};

bool checkCollision(GameObject* obj);
bool checkCollision(Vector2 points[4], Rectangle pos);
bool checkCollision(Vector2 points[4], Vector2 points2[4]);