#include "NPC.h"

NPC::NPC(NPC& npc):GameObject(npc),RectangleCollider(npc),HitAble(npc),Shop(npc)
{
	randomShop(10);
}

NPC::NPC(Rectangle pos, Rectangle collider,int hp, std::string name) :GameObject(pos, name), RectangleCollider(collider),HitAble(hp)
{


}

NPC::~NPC()
{
	if(body)
		delete body;
}

void NPC::update(float deltaTime)
{
	HitAble::update(deltaTime);
}

void NPC::randomShop(int n)
{
	const int nItems = Items->getSize();
	for (int i = 0; i < n; i++)
	{
		Item* item = Items->getObject(rand() % Items->getSize());
		if (!item)
			continue;
		int prise = item->getValue() * 2.5f;
		if (prise <= 0)
			prise = 1;
		int itemSize = 1;
		int itemStackSize = item->getStackMaxSize()/3;
		if (item->isStacable() && itemStackSize>=1)
			itemSize = (rand() % itemStackSize) + 1;
		addItem(item, prise, itemSize);
	}
}

void NPC::start()
{
	Rectangle pos = getPos();
	body = new CharacterBody("Resource/Character/Character_1/", pos.width, pos.width);
	body->setHairStyle(3);
	body->setBodyColor(BLUE);
	body->setLegsColor(BLACK);
	body->setEyeStyle(1);
	body->setHeadColor({ 241,194,125,255 });
	body->setHairColor(BLACK);

}

void NPC::onDestory()
{

}

void NPC::draw()
{
	Rectangle pos = getPos();
	body->draw(pos);
	pos.y -= 20;
	pos.height = 5;
	HitAble::draw(pos);

	if (collidersToDraw)
		RectangleCollider::draw(this);
}

void NPC::saveToJson(nlohmann::json& j)
{
	GameObject::saveToJson(j);
	HitAble::saveToJson(j);
	Shop::saveToJson(j);
}

void NPC::readFromJson(nlohmann::json& j)
{
	GameObject::readFromJson(j);
	HitAble::readFromJson(j);
	Shop::readFromJson(j);
}

bool NPC::dealDamage(float damage, float invisibleFrame)
{
	if (!HitAble::dealDamage(damage, invisibleFrame))
		return false;
	if (isObjectDead())
	{
		alive = false;
		if (body)
			body->updateCharacterState(CharacterState::Die);
	}
	return true;
}