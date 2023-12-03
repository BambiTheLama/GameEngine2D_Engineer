#include "Ammo.h"

AmmoType readAmmoType(std::string name)
{
	if(name.compare("Arrow"))
		return AmmoType::Arrow;
	if (name.compare("Bullet"))
		return AmmoType::Bullet;
	return AmmoType::Arrow;
}
std::string ammoTypeDescription()
{
	std::string s="";
	s += "Arrow (" + std::to_string((int)(AmmoType::Arrow)) + ")";
	s += "\nBullet (" + std::to_string((int)(AmmoType::Bullet)) + ")";
	return s;
}
std::string Ammo::description = "";
Ammo::Ammo(Ammo& ammo):StackItem(ammo)
{
	this->ammoType = ammo.ammoType;
	this->speed = ammo.speed;
	this->range = ammo.range;
	this->nCollisions = ammo.nCollisions;
	if (nCollisions > 0)
	{
		collisions = new Vector2[nCollisions];
		for (int i = 0; i < nCollisions; i++)
		{
			collisions[i] = ammo.collisions[i];
		}
	}

}
Ammo::Ammo(Rectangle pos, std::string name, float speed, float range, AmmoType ammoType):StackItem(pos,name,999)
{
	this->ammoType = ammoType;
	this->speed = speed;
	this->range = range;
	setStackSize(100);
}

Ammo::Ammo(nlohmann::json j) :StackItem(j)
{
	if (j.contains("Range"))
		range = j["Range"];
	else
		range = 400;
	if (j.contains("Speed"))
		speed = j["Speed"];
	else
		speed = 5;
	if (j.contains("AmmoType"))
		ammoType = (AmmoType)j["AmmoType"];
	else
		ammoType = AmmoType::Arrow;


	if (j.contains("LineCollsionN"))
	{
		nCollisions = j["LineCollsionN"];
		collisions = new Vector2[nCollisions];
		if (j.contains("Points"))
		{
			for (int i = 0; i < j["Points"].size(); i++)
			{
				collisions[i].x = j["Points"][i][0];
				collisions[i].y = j["Points"][i][1];
			}
		}


		for (int i = 0; i < nCollisions; i++)
		{
			if (j.contains(("Point" + std::to_string(i))))
			{
				Vector2 p;
				p.x = j[("Point" + std::to_string(i))][0];
				p.y = j[("Point" + std::to_string(i))][1];
				collisions[i] = p;
			}
			else
			{
				collisions[i] = { 0,0 };
			}

		}
	}


}

void Ammo::drawAmmo(Rectangle pos, float rotation,float chargeProcent,Vector2 orginOfset)
{
	Vector2 origin;
	origin = { pos.width * 3.0f/ 8.0f,pos.height *5.0f/ 8.0f };


	origin.x += pos.width / 2.69 * chargeProcent;
	origin.y -= pos.height / 2.69 * chargeProcent;
	
	origin.x += orginOfset.x;
	origin.y += orginOfset.y;
	DrawTexturePro(sprite->getTexture(), sprite->getTextureSize(), pos, origin, rotation, WHITE);
}

std::string Ammo::getDesctription()
{
	return std::string(TextFormat(description.c_str(), getName().c_str(), stackSize, speed, range));
}