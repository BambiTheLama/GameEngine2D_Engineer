#include "Bow.h"
#include "Ammo.h"
#include "../../Player/Eq.h"

Bow::Bow(Bow& b):Item(b)
{
	sprite = new SpriteController(*b.sprite);
	this->chargeTime = 0;
	this->chargeTimeMax = b.chargeTimeMax;
	this->origin = b.origin;
	rotation = 0;
}

Bow::Bow(Rectangle pos, std::string name) :Item(pos, name)
{
	std::string path = "Resource/Items/" + name + ".png";
	sprite = new SpriteController(path.c_str());
	this->chargeTime = 0;
	this->chargeTimeMax = 30;
	rotation = 0;
	origin = { 43.0f / 64.0f * pos.width, 21.0f / 64.0f * pos.height };

}

Bow::~Bow()
{
	delete sprite;
}

void Bow::update()
{
	Rectangle pos = getPos();
	rotation = cursorTarget({ pos.x ,pos.y }) - 45;
}

void Bow::draw()
{
	Rectangle textureSize = sprite->getTextureFrame((chargeTime * sprite->getHowMuchFrames()) / chargeTimeMax);
	Rectangle pos = getPos();

	DrawTexturePro(sprite->getTexture(), textureSize, pos, origin, rotation, WHITE);
	if (ammo != NULL && chargeTime > 0)
	{
		Vector2 ammoOffset = { -numberOfProjectal / 2,-numberOfProjectal / 2 };

		for (int i = 0; i < numberOfProjectal; i++)
		{
			ammo->drawAmmo(pos, rotation, (float)chargeTime / (float)chargeTimeMax,ammoOffset);
			ammoOffset.x += 1;
			ammoOffset.y += 1;
		}

	}

	//sprite->draw(getPos(), );
}

void Bow::drawAt(Rectangle pos)
{
	sprite->draw(pos, 0);
}

bool Bow::use()
{
	if (chargeTime == 0)
	{
		if(ammo==NULL)
			lookForAmmo();
		if (ammo != NULL)
		{
			setProjectalUsing();
		}
	}


	if (chargeTime + 1 < chargeTimeMax)
	{
		chargeTime++;
		return true;
	}
	return false;
}

void Bow::endUsing()
{
	if (chargeTime <= 0)
		return;
	chargeTime = 0;
	if (ammo == NULL)
	{
		lookForAmmo();
		return;
	}
	ammo->removeFromStack(numberOfProjectal);
	if (ammo->getStackSize() <= 0)
	{
		eq->removeItem(ammo);
		delete ammo;
		ammo = NULL;
		lookForAmmo();
	}
}

void Bow::lookForAmmo()
{
	if (eq == NULL)
		return;
	Item*** items = eq->getAllItems();
	for (int i = 0; i < EqHeight; i++)
		for (int j = 0; j < EqWight; j++)
		{
			if (items[i][j] == NULL || items[i][j]->getItemType() != ItemType::Ammo)
				continue;
			Ammo* ammo = dynamic_cast<Ammo*>(items[i][j]);
			if (ammo == NULL)
				continue;
			this->ammo = ammo;
			return;
		}
	
}

void Bow::setProjectalUsing()
{
	if (numberOfProjectalMax <= ammo->getStackSize())
		numberOfProjectal = numberOfProjectalMax;
	else
		numberOfProjectal = ammo->getStackSize();
}