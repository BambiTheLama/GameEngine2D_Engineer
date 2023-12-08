#pragma once
#include "../GameObject.h"
#include "../AddisionalTypes/AllTypes.h"
#include "Eq.h"
#include "MiniMap.h"
#include "../Crafting/CraftingStation.h"
enum class playerAnimationState {
    IDE = 0, MoveUp, MoveDown, MoveLeft, MoveRight = -3, Doge = 4, Die = 5
};
/// <summary>
/// Obiekt gracza nad kt�r� ma kontrol� u�ytkownik
/// </summary>
class Player :
    public GameObject, public RectangleCollider, public UserUI,public HitAble
{
    bool canMove = true;
    int pickUpRange = 100;
    float speed;
    float frame = 0;
    Eq* eq;
    MiniMap* miniMap;
    CraftingStation* crafting;
    AnimationController* animations;
    playerAnimationState state = playerAnimationState::IDE;

protected:
    Player(Player& obj);
public:

    /// <summary>
    /// Konstruktor od klasy gracza
    /// </summary>
    Player();
    /// <summary>
    /// Destruktor od klasy gracza
    /// </summary>
    ~Player();
    /// <summary>
    /// Metoda wykonywana przy starcie obiektu
    /// </summary>
    void start();
    /// <summary>
    /// Metoda aktualizuj�ca gracza
    /// </summary>
    void update(float deltaTime);
    /// <summary>
    /// Metoda od poruszania si� gracza
    /// </summary>
    void move(float deltaTime);
    /// <summary>
    /// Metoda rysuj�ca gracza
    /// </summary>
    void draw();
    /// <summary>
    /// Metoda zwracaj�ca TypObiektu
    /// </summary>
    /// <returns></returns>
    ObjectType getType() { return ObjectType::Player; }
    /// <summary>
    /// Aktualizuje receptury do craftowania
    /// </summary>
    void updateRecepies();
    /// <summary>
    /// Aktualizuje craftowanie przedmiot�w sprawdza czy co� craftujemy 
    /// </summary>
    void updateCrafting();
    /// <summary>
    /// Przyci�ga przedmioty z pewnej odleg�o�ci i dodaje do eq te co si� stykaj� z nami
    /// </summary>
    void pickUpItemsClose(float deltaTime);
    /// <summary>
    /// Rysuje interface
    /// </summary>
    virtual void drawInterface();
    /// <summary>
    /// Wszystko co jest wykonywane z Eq
    /// </summary>
    void updateEq(float deltaTime);

    virtual Player* clone() { return new Player(*this); }

    virtual void setCanMoveObject(bool canMove) { this->canMove = canMove; }

    bool isColliding() { return true; }

};

