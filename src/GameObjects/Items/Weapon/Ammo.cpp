#include "Ammo.h"

AmmoType readAmmoType(std::string name)
{
	if(name.compare("Arrow"))
		return AmmoType::Arrow;
	if (name.compare("Bullet"))
		return AmmoType::Bullet;
	return AmmoType::Arrow;
}

Ammo::Ammo(Ammo& ammo):StackItem(ammo)
{
	this->ammoType = ammo.ammoType;
	this->speed = ammo.speed;
	this->range = ammo.range;
}
Ammo::Ammo(Rectangle pos, std::string name, float speed, float range, AmmoType ammoType):StackItem(pos,name,999)
{
	this->ammoType = ammoType;
	this->speed = speed;
	this->range = range;
	setStackSize(100);
}

Ammo::Ammo(nlohmann::json j,int ID) :StackItem(j,ID)
{
	if (j[ID].contains("Range"))
		range = j[ID]["Range"];
	else
		range = 400;
	if (j[ID].contains("Speed"))
		speed = j[ID]["Speed"];
	else
		speed = 5;
	if (j[ID].contains("AmmoType"))
		ammoType = readAmmoType(j[ID]["AmmoType"]);
	else
		ammoType = AmmoType::Arrow;
}

void Ammo::drawAmmo(Rectangle pos, float rotation,float chargeProcent,Vector2 orginOfset)
{
	Vector2 origin;
	origin = { pos.width * 3.0f/ 8.0f,pos.height *5.0f/ 8.0f };


	origin.x += pos.width / 4 * chargeProcent;
	origin.y -= pos.height / 4 * chargeProcent;
	
	origin.x += orginOfset.x;
	origin.y += orginOfset.y;
	DrawTexturePro(sprite->getTexture(), sprite->getTextureSize(), pos, origin, rotation, WHITE);
}