#pragma once
#include "../Item.h"
class Ammo;
class Eq;
class Bow :
    public Item
{
    bool inHand = false;
    int chargeTime;
    int chargeTimeMax;
    int numberOfProjectal = 3;
    int numberOfProjectalMax = 3;
    float rotation=0;
    float speedMultiplier=1.0f;
    float rangeMultiplier=1.0f;
    Vector2 origin = { 0,pos.width };
    Eq* eq = NULL;
    Ammo* ammo = NULL;
    SpriteController* sprite;
private:
    Bow(Bow& b);
public:
    Bow(Rectangle pos, std::string name,int chargeTime,float speedMultiplier, float rangeMultiplier ,int numberOfProjectal=1);

    ~Bow();

    virtual void update();

    virtual void draw();

    virtual void drawAt(Rectangle pos);

    virtual bool use();

    virtual void updateAfterSwap();

    virtual void endUsing();

    virtual Bow* clone() { return new Bow(*this); }

    virtual ItemType getItemType() { return ItemType::Normal; }

    virtual void setEq(Eq* eq) { this->eq = eq; }

    void lookForAmmo();

    void setProjectalUsing();

    void setInHand(bool inHand) { this->inHand = inHand; }

    void spawnArrow();
};

