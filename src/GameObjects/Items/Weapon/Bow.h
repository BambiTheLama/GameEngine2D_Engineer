#pragma once
#include "../Item.h"
class Ammo;
class Eq;
class Bow :
    public Item
{
    Vector2 origin= { 0,pos.width };
    float rotation=0;
    int chargeTime;
    int chargeTimeMax;
    SpriteController* sprite;
    Eq* eq=NULL;
    Ammo* ammo = NULL;
private:
    Bow(Bow& b);
public:
    Bow(Rectangle pos, std::string name);

    ~Bow();

    virtual void update();

    virtual void draw();

    virtual void drawAt(Rectangle pos);

    virtual bool use();

    virtual void endUsing();

    virtual Bow* clone() { return new Bow(*this); }

    virtual ItemType getItemType() { return ItemType::Normal; }

    virtual void setEq(Eq* eq) { this->eq = eq; }

    void lookForAmmo();
};

