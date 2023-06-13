#include "Projectal.h"
#include <iostream>
#include "../../core/Scenes/GameScene.h"

Projectal::Projectal(Projectal& obj):GameObject(obj)
{

}

Projectal::Projectal(Rectangle pos, float rotation,float range):GameObject(pos)
{
	this->rotation = rotation;
	float multiplay = tan(rotation);
	this->range = range;
	this->speed = 5;

	delta = deltaFromDegree(rotation,speed);
}

Projectal::~Projectal()
{

}

void Projectal::update()
{
	pos.x += delta.x;
	pos.y += delta.y;
	range -= speed;
	if (range <= 0)
	{
		Game->deleteObject(this);
	}
	else
	{
		toUpdate--;
		if (toUpdate <= 0)
		{
			Game->updatePos(this);
			toUpdate = 5;

		}
			
	}
}

void Projectal::draw()
{
	//DrawRectanglePro(pos, { pos.width / 2, pos.height / 2 }, rotation, BLACK);
	DrawRectanglePro(pos, { 0, 0 }, 0, BLACK);
	
}