#pragma once
#include "../GameObject.h"
/// <summary>
/// Klasa która odpowiada za Pociski w naszej grze
/// </summary>
class Projectal :
    public GameObject
{
    float rotation;
    Vector2 delta;
    float range = 100;
    float speed=5;
    int toUpdate = 5;
protected:
    Projectal(Projectal& obj);
public:
    /// <summary>
    /// Konstruktor pocisku
    /// </summary>
    /// <param name="pos">Pozycja na któej ma siê pojawiæ pocisk</param>
    /// <param name="rotation">Rotacja pocisku w stopniach</param>
    Projectal(Rectangle pos, float rotation,float range=400);
    /// <summary>
    /// Destruktor klasy
    /// </summary>
    ~Projectal();
    /// <summary>
    /// Metoda aktualizuj¹ca
    /// </summary>
    void update();
    /// <summary>
    /// Metoda rysuj¹ca
    /// </summary>
    void draw();

    ObjectType getType() { return ObjectType::Projectal; }

    virtual Projectal* clone() { return new Projectal(*this); }
};

