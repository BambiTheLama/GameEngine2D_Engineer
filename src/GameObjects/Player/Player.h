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
/// Obiekt gracza nad któr¹ ma kontrolê u¿ytkownik
/// </summary>
class Player :
    public GameObject, public Collider , public UserUI
{
    float speed;
    AnimationController* animations;
    playerAnimationState state = playerAnimationState::IDE;
    float frame = 0;
    bool canMove = true;
    Eq* eq;
    CraftingStation* crafting;
    MiniMap* miniMap;
    int pickUpRange = 100;
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
    /// Metoda aktualizuj¹ca gracza
    /// </summary>
    void update();
    /// <summary>
    /// Metoda od poruszania siê gracza
    /// </summary>
    void move();
    /// <summary>
    /// Metoda rysuj¹ca gracza
    /// </summary>
    void draw();
    /// <summary>
    /// Metoda zwracaj¹ca TypObiektu
    /// </summary>
    /// <returns></returns>
    ObjectType getType() { return ObjectType::Player; }
    /// <summary>
    /// Aktualizuje receptury do craftowania
    /// </summary>
    void updateRecepies();
    /// <summary>
    /// Aktualizuje craftowanie przedmiotów sprawdza czy coœ craftujemy 
    /// </summary>
    void updateCrafting();
    /// <summary>
    /// Przyci¹ga przedmioty z pewnej odleg³oœci i dodaje do eq te co siê stykaj¹ z nami
    /// </summary>
    void pickUpItemsClose();
    /// <summary>
    /// Rysuje interface
    /// </summary>
    virtual void drawInterface();
    /// <summary>
    /// Wszystko co jest wykonywane z Eq
    /// </summary>
    void updateEq();

    virtual Player* clone() { return new Player(*this); }

    virtual void setCanMoveObject(bool canMove) { this->canMove = canMove; }

    bool isColliding() { return true; }
};

