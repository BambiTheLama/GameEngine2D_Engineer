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
    AmmoType ammoType;
protected:
    Ammo(Ammo& ammo);
public:
    Ammo(Rectangle pos, std::string name, AmmoType ammoType);

    virtual Ammo* clone() { return new Ammo(*this); }

    virtual ItemType getItemType() { return ItemType::Ammo; }

    void drawAmmo(Rectangle pos, float rotation, float chargeProcent);
};

