#pragma once
#include "../GameObject.h"
#include "../AddisionalTypes/AllTypes.h"
#include "../AddisionalTypes/Shop.h"
class NPC :
    public GameObject, public RectangleCollider,public HitAble,public Shop
{
    bool alive = true;
    CharacterBody* body = NULL;
    NPC(NPC& npc);
    void randomShop(int n);
public:
    NPC(Rectangle pos, Rectangle collider, int hp, std::string name);

    virtual ~NPC();

    virtual void update(float deltaTime);

    virtual void start();

    virtual void onDestory();

    virtual void draw();

    ObjectType getType() { return ObjectType::NPC; }

    virtual NPC* clone() { return new NPC(*this); }

    virtual bool destoryAfterRenderClear() { return !alive; }

    virtual void saveToJson(nlohmann::json& j);

    virtual void readFromJson(nlohmann::json& j);

    virtual bool dealDamage(float damage, float invisibleFrame);
};

