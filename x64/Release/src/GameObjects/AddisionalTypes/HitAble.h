#pragma once
#include "raylib.h"
#include "json.hpp"
/// <summary>
/// Interfejs od zadawania obra¿eñ Obiekt¹
/// </summary>

class HitAble
{
protected:
	float hp=0;
	float maxHp=0;
	float invisibleFrame=0;
	HitAble(HitAble& h);
public:

	HitAble(int hp);

	virtual void update(float deltaTime);

	virtual bool dealDamage(float damage,float invisibleFrame);

	virtual void draw(Rectangle pos);

	bool isObjectDead() { return hp <= 0; }
	
	void saveToJson(nlohmann::json& j);

	void readFromJson(nlohmann::json& j);


};

