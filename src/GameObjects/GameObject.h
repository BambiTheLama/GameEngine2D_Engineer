#pragma once
#include "raylib.h"
#include <math.h>
float cursorTarget(Vector2 objPos);
float degreeToRadius(float degree);
float radiusToDegree(float degree);
Vector2 deltaFromDegree(float degree,float speed=1);
/// <summary>
/// Enum określający do jakiego typu należy dany obiekt
/// </summary>
enum class ObjectType
{
	NPC, Item, Block, Particle, Player, NON, Projectal,
};
/// <summary>
/// Klasa bazowa dla wszystkich obiektów gry
/// </summary>
class GameObject
{
protected:
	Rectangle pos;
	Vector2 movePos = { 0,0 };
	GameObject(GameObject& obj);
public:

	GameObject(Rectangle pos);
	/// <summary>
	/// Wiztualny destruktor by był wywołany odpowiedni z klas dziedziczących
	/// </summary>
	virtual ~GameObject() {};
	/// <summary>
	/// Metoda aktualizująca obiekt
	/// </summary>
	virtual void update()=0;
	/// <summary>
	/// Metoda do rysowania obiektu
	/// </summary>
	virtual void draw()=0;
	/// <summary>
	/// Metoda get definiująca jakiego typu jest obiekt
	/// </summary>
	/// <returns></returns>
	virtual ObjectType getType() = 0;

	virtual void setMovePos(Vector2 movePos) { this->movePos = movePos; }

	virtual Rectangle getPos() { return { movePos.x + pos.x,movePos.y + pos.y,pos.width,pos.height }; }

	virtual GameObject* clone() = 0;
};

