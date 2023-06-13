#pragma once
#include "../GameObject.h"
#include "../Items/Weapon/Weapon.h"
/// <summary>
/// Obiekt gracza nad któr¹ ma kontrolê u¿ytkownik
/// </summary>
class Player :
    public GameObject
{
    float speed;
    Weapon* weapon;
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

    virtual Player* clone() { return new Player(*this); }
};

