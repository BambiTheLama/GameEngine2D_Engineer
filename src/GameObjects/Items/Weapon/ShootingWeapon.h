#pragma once
#include "Weapon.h"
#include "../../Projectals/Projectal.h"
class ShootingWeapon :
    public Weapon
{
    float rotation;
    Vector2 origin;
    Projectal* projectal=NULL;
protected:
    ShootingWeapon(ShootingWeapon& obj);
public:
    ShootingWeapon(Rectangle pos, std::string name);

    ~ShootingWeapon();

    virtual void update();

    virtual void draw();

    virtual void drawAt(Rectangle pos);

    virtual bool use();

    virtual WeaponType getWeaponType() { return WeaponType::Range; }

    virtual ShootingWeapon* clone() { return new ShootingWeapon(*this); }
};

