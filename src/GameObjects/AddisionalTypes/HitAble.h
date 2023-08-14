#pragma once
#include "raylib.h"
/// <summary>
/// Interfejs od zadawania obra¿eñ Obiekt¹
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

	virtual bool dealDamage(int damage,float invisibleFrame=0);

	virtual void draw(Rectangle pos);

	bool isObjectDead() { return hp <= 0; }

	virtual Rectangle getCollisionPos() = 0;
};

