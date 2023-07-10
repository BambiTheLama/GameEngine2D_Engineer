#include "Weapon.h"

Weapon::Weapon(Weapon& obj):Item(obj)
{

}

Weapon::Weapon(Rectangle pos, std::string name):Item(pos,name)
{

}

void Weapon::update()
{
	if(CDR>0)
		CDR--;
}

void Weapon::draw()
{

}

bool Weapon::use()
{
	return false;
}
