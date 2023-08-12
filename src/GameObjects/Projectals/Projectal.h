#pragma once
#include "../GameObject.h"
#include "../AddisionalTypes/AllTypes.h"
/// <summary>
/// Klasa kt�ra odpowiada za Pociski w naszej grze
/// </summary>
class Projectal :
    public GameObject , public Collider
{
    SpriteController* sprite=NULL;
    float rotation;
    Vector2 delta;
    float range;
    float speed;
    int toUpdate;
protected:
    Projectal(Projectal& obj);
public:

    Projectal(Rectangle pos,float speed, float rotation,float range,SpriteController* sprite,Vector2 collision[4]);

    ~Projectal();

    void update();

    void draw();

    void setRotation(float rotation) { this->rotation = rotation; delta = deltaFromDegree(rotation, speed);}

    ObjectType getType() { return ObjectType::Projectal; }

    virtual Projectal* clone() { return new Projectal(*this); }
};

