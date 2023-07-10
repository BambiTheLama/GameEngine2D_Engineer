#pragma once
#include "../Item.h"

enum class WeaponType
{
    Mele, Range, Magic, NON
};

class Weapon :
    public Item
{
protected:
    int CDR=0;
    int CDRMAX=15;

    Weapon(Weapon& obj);
public:
    Weapon(Rectangle pos, std::string name);

    virtual void update();

    virtual void draw();

    virtual bool use();

    virtual WeaponType getWeaponType() { return WeaponType::NON; }

    virtual Weapon* clone() { return new Weapon(*this); }
};

