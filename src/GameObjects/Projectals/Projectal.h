#pragma once
#include "../GameObject.h"
#include "../AddisionalTypes/AllTypes.h"
/// <summary>
/// Klasa która odpowiada za Pociski w naszej grze
/// </summary>
class Projectal :
    public GameObject , public LinesCollider
{
    SpriteController* sprite=NULL;
    float rotation;
    Vector2 delta;
    float range;
    float speed;
    int toUpdate;
    bool destory = false;
protected:
    Projectal(Projectal& obj);
public:

    Projectal(Rectangle pos, float speed, float rotation, float range,
        SpriteController* sprite, Vector2 collision[4], CollisionsCheckType collisionType);

    ~Projectal();

    void update();

    void draw();

    void setRotation(float rotation) { this->rotation = rotation; delta = deltaFromDegree(rotation, speed);}

    ObjectType getType() { return ObjectType::Projectal; }

    virtual Projectal* clone() { return new Projectal(*this); }

    void onCollisionHitable(HitAble* hit);

    void onCollisionDestroyAble(DestroyAble* dest);
};

