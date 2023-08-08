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

void HitAble::update()
{
	if (invisibleFrame > 0)
		invisibleFrame--;
}
void HitAble::draw(Rectangle pos)
{
	DrawRectangleRec(pos, GRAY);
	DrawRectangle(pos.x, pos.y, pos.width * hp / maxHp, pos.height, GREEN);
}
bool HitAble::dealDamage(int damage, int invisibleFrame)
{
	if(this->invisibleFrame > 0)
	{
		return false;
	}
	hp -= damage;
	this->invisibleFrame = invisibleFrame;
	GameObject* obj = dynamic_cast<GameObject*>(this);
	if (obj != NULL)
	{
		std::string text = std::to_string(damage);
		Game->addObject(new TextParticle(obj->getPos(), text));
	}
	
}