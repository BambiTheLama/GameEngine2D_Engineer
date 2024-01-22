#include "HitAble.h"
#include "../../core/Scenes/GameScene.h"
#include "../Particles/TextParticle.h"

HitAble::HitAble(HitAble& h)
{
	hp = h.hp;
	maxHp = h.maxHp;
}

HitAble::HitAble(int hp)
{
	this->maxHp = hp;
	this->hp = hp;
}

void HitAble::update(float deltaTime)
{
	if (invisibleFrame > 0)
		invisibleFrame-=deltaTime;
}
void HitAble::draw(Rectangle pos)
{
	DrawRectangleRec(pos, GRAY);
	DrawRectangle(pos.x, pos.y, pos.width * hp / maxHp, pos.height, GREEN);
}
bool HitAble::dealDamage(float damage, float invisibleFrame)
{
	if(this->invisibleFrame > 0)
	{
		return false;
	}
	hp -= damage;
	this->invisibleFrame = invisibleFrame;
	GameObject* obj = dynamic_cast<GameObject*>(this);
	if (obj)
	{
		std::string text = std::to_string((int)damage);
		Game->addObject(new TextParticle(obj->getPos(), text));
	}
	return true;
}

void HitAble::saveToJson(nlohmann::json& j)
{
	j["HP"][0] = hp;
	j["HP"][1] = maxHp;

}

void HitAble::readFromJson(nlohmann::json& j)
{
	hp = j["HP"][0];
	maxHp = j["HP"][1];
}