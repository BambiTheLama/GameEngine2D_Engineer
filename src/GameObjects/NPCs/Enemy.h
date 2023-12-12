#pragma once
#include "../GameObject.h"
#include "../AddisionalTypes/AllTypes.h"
class Enemy :
    public GameObject, public RectangleCollider, public HitAble
{
    Enemy(Enemy& e);
public:
    Enemy();

    Enemy(Rectangle pos,Rectangle colliderBox, std::string name);

    virtual ~Enemy();

    virtual void update(float deltaTime);

    virtual void draw();

    virtual bool dealDamage(float damage, float invisibleFrame);

    ObjectType getType() { return ObjectType::NPC; }

    virtual Enemy* clone() { return new Enemy(*this); }

    virtual bool destoryAfterRenderClear() { return false; }

    virtual void saveToJson(nlohmann::json& j);

    virtual void readFromJson(nlohmann::json& j);
};

