#include "Ammo.h"

Ammo::Ammo(Ammo& ammo):StackItem(ammo)
{
	this->ammoType = ammo.ammoType;
}
Ammo::Ammo(Rectangle pos, std::string name, AmmoType ammoType):StackItem(pos,name,999)
{
	this->ammoType = ammoType;
	setStackSize(100);
}

void Ammo::drawAmmo(Rectangle pos, float rotation,float chargeProcent)
{
	Vector2 origin;
	origin = { pos.width / 2,pos.height / 2 };
	if (IsKeyUp(KEY_ONE))
	{
		origin.x += 5.0f * chargeProcent;
		origin.y -= 5.0f * chargeProcent;
	}

	DrawTexturePro(sprite->getTexture(), sprite->getTextureSize(), pos, origin, rotation, WHITE);
}