#pragma once
#include "../GameObject.h"
#include "../Items/Weapon/Weapon.h"
#include "../AddisionalTypes/AllTypes.h"
#include "Eq.h"
#include "MiniMap.h"

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
    Weapon* weapon;
    AnimationController* animations;
    playerAnimationState state = playerAnimationState::IDE;
    float frame = 0;
    bool canMove = true;
    Eq* eq;
    MiniMap* miniMap;
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

    virtual void drawInterface();

    virtual Player* clone() { return new Player(*this); }

    virtual void setCanMoveObject(bool canMove) { this->canMove = canMove; }

    bool isColliding() { return true; }
};

