#include "Player.h"
#include <math.h>
#include <iostream>
#include "../../core/Scenes/GameScene.h"
#include "../Projectals/Projectal.h"
#include "../ItemFactory.h"

Player::Player(Player& obj):GameObject(obj)
{

}

Player::Player():GameObject({ 400,400,64,64 })
{
	speed = 2;
	Item* i= Items->getObject(0);
	weapon = dynamic_cast<Weapon*>(i);
}
Player::~Player()
{
	printf("UMAR£EM\n");
}
void Player::update()
{
	move();
}

void Player::move()
{
	Rectangle posTmp = getPos();
	if (IsKeyDown(KEY_A))
	{
		pos.x -= speed;
	}
	if (IsKeyDown(KEY_D))
	{
		pos.x += speed;
	}
	if (IsKeyDown(KEY_W))
	{
		pos.y -= speed;
	}
	if (IsKeyDown(KEY_S))
	{
		pos.y += speed;
	}
	if (checkCollision(this))
	{
		pos = posTmp;
	}
	weapon->setMovePos({ pos.x,pos.y });
	weapon->update();
	Game->updatePos(this);
}
#define changePos {int s=6;pos.x += s;pos.y += s;pos.width -= s+s;pos.height -= s+s; }
void Player::draw()
{
	Rectangle pos = getPos();
	DrawRectangleRec(pos, RED);
	changePos
	DrawRectangleRec(pos, GREEN);
	changePos
	DrawRectangleRec(pos, BLUE);
	changePos
	DrawRectangleRec(pos, YELLOW);
	weapon->draw();
}