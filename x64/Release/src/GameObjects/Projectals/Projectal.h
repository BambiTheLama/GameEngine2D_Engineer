#pragma once
#include "../GameObject.h"
#include "../AddisionalTypes/AllTypes.h"
/// <summary>
/// Klasa która odpowiada za Pociski w naszej grze
/// </summary>
class Projectal :
    public GameObject , public LinesCollider
{
    bool destory = false;
    int toUpdate;
    float range;
    float speed;
    float rotation;
    Vector2 delta;
    SpriteController* sprite = NULL;
protected:
    Projectal(Projectal& obj);
public:

    Projectal(Rectangle pos, float speed, float rotation, float range,
        SpriteController* sprite, Vector2 *collision,int n, CollisionsCheckType collisionType);

    ~Projectal();

    void update(float deltaTime);

    void draw();

    void setRotation(float rotation) { this->rotation = rotation; delta = deltaFromDegree(rotation, speed);}

    ObjectType getType() { return ObjectType::Projectal; }

    virtual Projectal* clone() { return new Projectal(*this); }

    void onCollisionHitable(HitAble* hit);

    void onCollisionDestroyAble(DestroyAble* dest);

    virtual bool destoryAfterRenderClear() { return true; }
};

