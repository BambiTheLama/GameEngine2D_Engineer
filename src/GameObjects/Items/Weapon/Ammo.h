#pragma once
#include "../StackItem.h"

enum class AmmoType
{
    Arrow,
    Bullet,
};

class Ammo :
    public StackItem
{
    float speed;
    float range;
    AmmoType ammoType;

protected:
    Ammo(Ammo& ammo);
public:
    Ammo(Rectangle pos, std::string name,float speed,float range, AmmoType ammoType);

    virtual Ammo* clone() { return new Ammo(*this); }

    virtual ItemType getItemType() { return ItemType::Ammo; }

    void drawAmmo(Rectangle pos, float rotation, float chargeProcent, Vector2 orginOfset);

    float getSpeed() const { return speed; }

    float getRange() const { return range; }
};

