#pragma once
#include "raylib.h"
/// <summary>
/// Interfejs od zadawania obra�e� Obiekt�
/// </summary>
class HitAble
{
protected:
	int hp=0;
	int maxHp=0;
	float invisibleFrame=0;
	HitAble(HitAble& h);
public:

	HitAble(int hp);

	virtual void update(float deltaTime);

	virtual bool dealDamage(int damage,float invisibleFrame);

	virtual void draw(Rectangle pos);

	bool isObjectDead() { return hp <= 0; }

	virtual Rectangle getCollisionPos() = 0;
};

