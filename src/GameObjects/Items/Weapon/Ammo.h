#pragma once
#include "../StackItem.h"

enum class AmmoType
{
    Arrow,
    Bullet,
};

AmmoType readAmmoType(std::string name);

class Ammo :
    public StackItem
{
    int nCollisions;
    float speed;
    float range;
    AmmoType ammoType;
    Vector2* collisions;
protected:
    Ammo(Ammo& ammo);
public:
    Ammo(Rectangle pos, std::string name,float speed,float range, AmmoType ammoType);

    Ammo(nlohmann::json j, int ID);

    virtual Ammo* clone() { return new Ammo(*this); }

    virtual ItemType getItemType() { return ItemType::Ammo; }

    void drawAmmo(Rectangle pos, float rotation, float chargeProcent, Vector2 orginOfset);

    float getSpeed() const { return speed; }

    float getRange() const { return range; }

    Vector2* getCollsions()const { return collisions; }

    int getNCollisions()const { return nCollisions; }
};

