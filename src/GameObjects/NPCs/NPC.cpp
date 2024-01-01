#include "NPC.h"

NPC::NPC(NPC& npc):GameObject(npc),RectangleCollider(npc),HitAble(npc)
{

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

void NPC::start()
{
	Rectangle pos = getPos();
	body = new CharacterBody("Resource/Character/Character_1/", pos.width, pos.width);
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
}

void NPC::readFromJson(nlohmann::json& j)
{
	GameObject::readFromJson(j);
	HitAble::readFromJson(j);
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