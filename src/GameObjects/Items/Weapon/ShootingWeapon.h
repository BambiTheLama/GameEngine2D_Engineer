#pragma once
#include "Weapon.h"
class ShootingWeapon :
    public Weapon
{
    float rotation;
    Vector2 orgin;
protected:
    ShootingWeapon(ShootingWeapon& obj);
public:
    ShootingWeapon(Rectangle pos);

    ~ShootingWeapon();

    virtual void update();

    virtual void draw();

    virtual bool use();

    virtual WeaponType getWeaponType() { return WeaponType::Range; }

    virtual ShootingWeapon* clone() { return new ShootingWeapon(*this); }
};

