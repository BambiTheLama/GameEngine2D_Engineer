#pragma once
#include "../GameObject.h"
#include "../AddisionalTypes/AllTypes.h"
#include "PathFinding.h"
class Enemy :
    public GameObject, public RectangleCollider, public HitAble,public UserUI
{
    GameObject* target = NULL;
    PathFinding* path = NULL;
    Item* item;
    float range = 1000;
    float speed = 30;
    Enemy(Enemy& e);
public:
    Enemy();

    Enemy(Rectangle pos,Rectangle colliderBox, std::string name);

    virtual ~Enemy();

    virtual void update(float deltaTime);

    void findPath();

    Vector2 getMoveVector();

    virtual void start();

    virtual void onDestory();

    virtual void draw();

    virtual void drawInterface();

    virtual bool dealDamage(float damage, float invisibleFrame);

    ObjectType getType() { return ObjectType::NPC; }

    virtual Enemy* clone() { return new Enemy(*this); }

    virtual bool destoryAfterRenderClear() { return false; }

    virtual void saveToJson(nlohmann::json& j);

    virtual void readFromJson(nlohmann::json& j);

    float getDistanceToTarget();
};

