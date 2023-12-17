#pragma once
#include "raylib.h"
#include <math.h>
#include "../core/Controllers/AnimationController.h"
#include "../core/Properties.h"
#include "json.hpp"

/// <summary>
/// Zwraca kat od obiektu do pozycji kursora
/// </summary>
/// <param name="objPos">Pozycja obiketu</param>
/// <returns>Kat padania</returns>
float cursorTarget(Vector2 objPos);
/// <summary>
/// Zwraca kat od obiektu do pozycji kursora
/// </summary>
/// <param name="objPos">Pozycja obiketu</param>
/// <param name="cursor">Pozycja cursora</param>
/// <returns>Kat padania</returns>
float cursorTarget(Vector2 objPos, Vector2 cursor);
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
/// Zwraca jak obiekt powinien siê poruszaæ xy z podan¹ prêdkoœci¹ i k¹tem
/// </summary>
/// <param name="degree"></param>
/// <param name="speed"></param>
/// <returns></returns>
Vector2 deltaFromDegree(float degree,float speed=1);

/// <summary>
/// Enum okreœlaj¹cy do jakiego typu nale¿y dany obiekt
/// </summary>
enum class ObjectType
{
	NPC, Item, Block, Particle, Structure, Player, Projectal, NON,
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
	int chunkX, chunkY;
	/// <summary>
	/// Kostruktor pomagajacy kopiowac dane z obiektu podanego w parametrze konstruktor glownie uzywany przy kolonowaniu obiektow
	/// </summary>
	/// <param name="obj"></param>
	GameObject(GameObject& obj);
public:
	/// <summary>
	/// Konstruktor sluzacy glownie do tworzenia obiektow w fabrykach obiektow
	/// </summary>
	/// <param name="pos">Pozycja obiektu</param>
	/// <param name="name">Nazwa obiektu</param>
	GameObject(Rectangle pos,std::string name);
	/// <summary>
	/// Konstruktor wczytujace dane z pliku json uzywane przy wczytywaniu przedmiotow z pliku json
	/// </summary>
	/// <param name="j"></param>
	GameObject(nlohmann::json& j);
	/// <summary>
	/// Wiztualny destruktor by by³ wywo³any odpowiedni z klas dziedzicz¹cych
	/// </summary>
	virtual ~GameObject();
	/// <summary>
	/// Metoda aktywowana przy ustawieniu obiektu na mapie
	/// </summary>
	virtual void start(){}
	/// <summary>
	/// Funkcja wykonywana przy usuwaniu obiektu
	/// </summary>
	virtual void onDestory(){}
	/// <summary>
	/// Metoda aktualizuj¹ca obiekt
	/// </summary>
	virtual void update(float deltaTime)=0;
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
	virtual void setMovePos(Vector2 movePos) { pos.x = movePos.x; pos.y = movePos.y; generateChunk(); }
	/// <summary>
	/// Dodaje do pozycji wartosc przemieszczenia
	/// </summary>
	/// <param name="toAdd">Przemieszczenie</param>
	virtual void addToPos(Vector2 toAdd) { pos.x += toAdd.x, pos.y += toAdd.y; generateChunk(); }
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
	/// <summary>
	/// Zwraca nazwê obiektu
	/// </summary>
	/// <returns>Nazwa obiektu</returns>
	virtual std::string getName() { return name; }
	/// <summary>
	/// Okresla czy  obiekt ma zostac zniszczony po usunieciu chanku
	/// </summary>
	/// <returns></returns>
	virtual bool destoryAfterRenderClear() { return false; }
	/// <summary>
	/// Zapisywanie obiektu do pliku json
	/// </summary>
	/// <param name="j"></param>
	virtual void saveToJson(nlohmann::json &j);
	/// <summary>
	/// Wczytanie danych z pliku json
	/// </summary>
	/// <param name="j"></param>
	virtual void readFromJson(nlohmann::json& j);
	/// <summary>
	/// Zwraca informacje na ktoryk kawalku mapy jestesmy w osi X
	/// </summary>
	/// <returns></returns>
	int getChunkX()const { return chunkX; }
	/// <summary>
	/// Zwraca informacje na ktoryk kawalku mapy jestesmy w osi Y
	/// </summary>
	/// <returns></returns>
	int getChunkY()const { return chunkY; }
	/// <summary>
	/// Generuje informacjê na ktorych kawalkach mapy jestesmy
	/// </summary>
	void generateChunk();
	friend class Factory;
	friend class BlockFactory;
	friend class ItemFactory;
	friend class StructuresFactory;
	friend class NPCFactory;
};
/// <summary>
/// Zwraca obiekt z odpowiedniej fabryki o podanym ID
/// </summary>
/// <param name="type">Typ obiektu okreslajacy fabryke</param>
/// <param name="ID">Identyfikator obiektu</param>
/// <returns></returns>
GameObject* getObjFromFactory(ObjectType type, int ID);
