#pragma once
#include "../GameObject.h"
/// <summary>
/// Klasa kt�ra odpowiada za Pociski w naszej grze
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
    /// <param name="pos">Pozycja na kt�ej ma si� pojawi� pocisk</param>
    /// <param name="rotation">Rotacja pocisku w stopniach</param>
    Projectal(Rectangle pos, float rotation,float range=400);
    /// <summary>
    /// Destruktor klasy
    /// </summary>
    ~Projectal();
    /// <summary>
    /// Metoda aktualizuj�ca
    /// </summary>
    void update();
    /// <summary>
    /// Metoda rysuj�ca
    /// </summary>
    void draw();
    /// <summary>
    /// Ustaw rotacj� pocisku
    /// </summary>
    /// <param name="rotation">K�t obrotu</param>
    void setRotation(float rotation) { this->rotation = rotation; delta = deltaFromDegree(rotation, speed);}

    ObjectType getType() { return ObjectType::Projectal; }

    virtual Projectal* clone() { return new Projectal(*this); }
};

