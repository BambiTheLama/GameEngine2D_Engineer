#pragma once
#include "../GameObject.h"
#include "../AddisionalTypes/AllTypes.h"
class Enemy :
    public GameObject, public Collider, public HitAble
{
    Enemy(Enemy& e);
public:
    Enemy();
    Enemy(Rectangle pos,Rectangle colliderBox, std::string name);

    virtual ~Enemy();

    virtual void update(float deltaTime);

    virtual void draw();

    virtual bool dealDamage(int damage, int invisibleFrame = 0);

    ObjectType getType() { return ObjectType::NPC; }

    virtual Enemy* clone() { return new Enemy(*this); }

    Rectangle getCollisionPos();
};

