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

void Ammo::drawAmmo(Rectangle pos, float rotation,float chargeProcent,Vector2 orginOfset)
{
	Vector2 origin;
	origin = { pos.width * 3.0f/ 8.0f,pos.height *5.0f/ 8.0f };

	if (IsKeyUp(KEY_ONE))
	{
		origin.x += pos.width / 4 * chargeProcent;
		origin.y -= pos.height / 4 * chargeProcent;
	}
	origin.x += orginOfset.x;
	origin.y += orginOfset.y;
	DrawTexturePro(sprite->getTexture(), sprite->getTextureSize(), pos, origin, rotation, WHITE);
}