#include "Bow.h"
#include "Ammo.h"
#include "../../Player/Eq.h"
#include "../../Projectals/Projectal.h"
#include ",,/../../../../core/Scenes/GameScene.h"

std::string Bow::description = "";

Bow::Bow(Bow& b):Item(b)
{
	sprite = new SpriteController(*b.sprite);

	this->chargeTime = 0;
	this->chargeTimeMax = b.chargeTimeMax;

	this->origin = b.origin;
	rotation = 0;

	this->numberOfProjectalMax = b.numberOfProjectal;
	this->numberOfProjectal = b.numberOfProjectal;

	this->speedMultiplier = b.speedMultiplier;
	this->rangeMultiplier = b.rangeMultiplier;
}

Bow::Bow(Rectangle pos, std::string name, float chargeTime, float speedMultiplier, float rangeMultiplier, int numberOfProjectal) :Item(pos, name)
{
	std::string path = "Resource/Items/" + name + ".png";
	sprite = new SpriteController(path.c_str());

	this->chargeTime = 0;
	this->chargeTimeMax = chargeTime;

	origin = { 43.0f / 64.0f * pos.width, 21.0f / 64.0f * pos.height };
	rotation = 0;

	this->numberOfProjectalMax = numberOfProjectal;
	this->numberOfProjectal = numberOfProjectal;

	this->speedMultiplier = speedMultiplier;
	this->rangeMultiplier = rangeMultiplier;
}
Bow::Bow(nlohmann::json j):Item(j)
{
	origin = { 43.0f / 64.0f * pos.width, 21.0f / 64.0f * pos.height };
	chargeTime = 0;
	rotation = 0;
	std::string path = "Resource/Items/" + std::string(j["Name"]) + ".png";
	sprite = new SpriteController(path.c_str());
	if (j.contains("Projectals"))
		numberOfProjectalMax = j.contains("Projectals");
	else
		numberOfProjectalMax = 1;
	if (j.contains("Range"))
		rangeMultiplier = j["Range"];
	else
		rangeMultiplier = 1;
	if (j.contains("Speed"))
		speedMultiplier = j["Speed"];
	else
		speedMultiplier = 1;
	if (j.contains("UseTime"))
		chargeTimeMax = j["UseTime"];
	else
		chargeTimeMax = 1;
}
Bow::~Bow()
{
	delete sprite;
}
void Bow::update(float deltaTime)
{
	Rectangle pos = getPos();
	rotation = cursorTarget({ pos.x ,pos.y }) - 45;
}

void Bow::update(float deltaTime, Vector2 curosrPos)
{
	Rectangle pos = getPos();
	rotation = cursorTarget({ pos.x ,pos.y }, curosrPos) - 45;
}

void Bow::draw()
{
	if (!inHand)
	{
		sprite->draw(getPos(), 0);
		return;
	}
	Rectangle textureSize = sprite->getTextureFrame((chargeTime * sprite->getHowMuchFrames()) / chargeTimeMax);
	Rectangle pos = getPos();

	DrawTexturePro(sprite->getTexture(), textureSize, pos, origin, rotation, WHITE);
	if (ammo && chargeTime > 0)
	{
		Vector2 ammoOffset = { -numberOfProjectal / 2,-numberOfProjectal / 2 };
		Rectangle pos2 = getPos();
		pos2.x = pos.x;
		pos2.y = pos.y;
		for (int i = 0; i < numberOfProjectal; i++)
		{
			ammo->drawAmmo(pos2, rotation, (float)chargeTime / (float)chargeTimeMax,ammoOffset);
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

bool Bow::use(float deltaTime, Vector2 curosrPos)
{
	if (chargeTime == 0)
	{
		if(!ammo)
			lookForAmmo();
		if (ammo)
		{
			setProjectalUsing();
		}
	}


	if (chargeTime < chargeTimeMax)
	{
		chargeTime += deltaTime;
		if (chargeTime >= chargeTimeMax)
		{
			spawnArrow();
			chargeTime = 0;
		}

		return true;
	}
	return false;
}
void Bow::updateAfterSwap()
{
	ammo = NULL;
	lookForAmmo();
}
void Bow::endUsing()
{
	if (chargeTime <= 0)
		return;
	spawnArrow();
	chargeTime = 0;

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

void Bow::spawnArrow()
{
	if (!ammo)
		lookForAmmo();
	if (!ammo)
		return;
	
	Rectangle pos = getPos();
	Rectangle pos2 = ammo->getPos();
	pos.width = pos2.width;
	pos.height = pos2.height;
	Vector2* col = ammo->getCollsions();
	int n = ammo->getNCollisions();
	pos.x -= numberOfProjectal / 2;
	pos.y -= numberOfProjectal / 2;
	for (int i = 0; i < numberOfProjectal; i++)
	{
		float procent = (float)chargeTime / (float)chargeTimeMax;
		float speed = ammo->getSpeed() * speedMultiplier * procent;
		float range = ammo->getRange() * rangeMultiplier * procent;

		Projectal* pro = new Projectal(pos, speed, rotation, range, ammo->getSprite(),
			col, n, CollisionsCheckType::All);
		pro->addObjToIgnore(holdingObj);
		Game->addObject(pro);
		pos.x++;
		pos.y++;
	}
	ammo->removeFromStack(0);
	if (ammo->getStackSize() <= 0)
	{
		eq->removeItem(ammo);
		delete ammo;
		ammo = NULL;
		lookForAmmo();
	}

}

std::string Bow::getDesctription()
{
	return std::string(TextFormat(description.c_str(), getName().c_str(), chargeTimeMax, speedMultiplier, rangeMultiplier, numberOfProjectalMax));
}