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
    bool alive = true;
    float deadTimer = 2;
    float goTime = 0;
    CharacterBody* body;
    Enemy(Enemy& e);
public:
    Enemy();

    Enemy(Rectangle pos,Rectangle colliderBox, std::string name);

    virtual ~Enemy();

    virtual void update(float deltaTime);

    virtual void move(float deltaTime);

    virtual void itemUpdate(float deltaTime);

    virtual void bodyUpdate(float deltaTime);

    void findPath();

    Vector2 getMoveVector();

    virtual void start();

    virtual void onDestory();

    virtual void draw();

    virtual void drawInterface();

    virtual bool dealDamage(float damage, float invisibleFrame);

    ObjectType getType() { return ObjectType::Enemy; }

    virtual Enemy* clone() { return new Enemy(*this); }

    virtual bool destoryAfterRenderClear() { return !alive; }

    virtual void saveToJson(nlohmann::json& j);

    virtual void readFromJson(nlohmann::json& j);

    float getDistanceToTarget();
};

