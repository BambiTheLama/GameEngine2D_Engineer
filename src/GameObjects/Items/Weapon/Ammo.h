#pragma once
#include "../StackItem.h"

enum class AmmoType
{
    Arrow,
    Bullet,

    EnumSize
};

std::string ammoTypeDescription();

AmmoType readAmmoType(std::string name);

class Ammo :
    public StackItem
{
    int nCollisions=0;
    float speed;
    float range;
    AmmoType ammoType;
    Vector2* collisions=NULL;
    static std::string description;
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

    Vector2* getCollsions() { return collisions; }

    int getNCollisions() { return nCollisions; }

    virtual std::string getDesctription();
    friend class ItemFactory;
};

