#include "Player.h"
#include <math.h>
#include <iostream>
#include "../../core/Scenes/GameScene.h"
#include "../Projectals/Projectal.h"
#include "../ItemFactory.h"

Player::Player(Player& obj) :GameObject(obj), Collider(obj)
{
	animations = new AnimationController(*obj.animations);
}

Player::Player():GameObject({ 400,400,64,64 },"Player"), Collider({pos.width / 3,pos.height / 4,pos.width / 3,pos.width / 2})
{
	speed = 2;
	Item* i= Items->getObject(0);
	weapon = dynamic_cast<Weapon*>(i);
	int n = 6;
	std::string names[6] = { "IDE","MoveUp","MoveDown","MoveLeft","Doge","Die" };
	std::vector<SpriteController*> sprites;
	for (int i = 0; i < n; i++)
	{
		std::string path = "Resource/Player/" + names[i] + ".png";
		sprites.push_back(new SpriteController(path.c_str()));
		
	}
	animations = new AnimationController(sprites);
}
Player::~Player()
{
	if(Game!=NULL)
		Game->removeUserUI(this);
	delete animations;
}

void Player::start()
{
	Game->addUserUI(this);
}

void Player::update()
{
	move();
}

void Player::move()
{
	
	Vector2 posTmp = { 0,0 };
	if (canMove)
	{
		if (IsKeyDown(KEY_A))
		{
			posTmp.x -= speed;
		}
		if (IsKeyDown(KEY_D))
		{
			posTmp.x += speed;
		}
		if (IsKeyDown(KEY_W))
		{
			posTmp.y -= speed;
		}
		if (IsKeyDown(KEY_S))
		{
			posTmp.y += speed;
		}

		if (posTmp.x != 0)
		{
			if (posTmp.x > 0)
				state = playerAnimationState::MoveRight;
			else
				state = playerAnimationState::MoveLeft;
		}
		if (posTmp.y != 0)
		{
			if (posTmp.y > 0)
				state = playerAnimationState::MoveDown;
			else
				state = playerAnimationState::MoveUp;
		}
		if (IsKeyDown(KEY_SPACE))
		{
			state = playerAnimationState::Doge;
		}
	}
	
	Rectangle pos = getPos();
	setMovePos({ posTmp.x + pos.x, pos.y + posTmp.y });
	if (isCollidingWithSomething(this))
	{
		setMovePos({ pos.x, pos.y });
	}
	weapon->setMovePos({ pos.x+pos.width/2,pos.y+pos.height/2 });
	weapon->update();
	Game->updatePos(this);
}
#define changePos {int s=6;pos.x += s;pos.y += s;pos.width -= s+s;pos.height -= s+s; }
void Player::draw()
{
	Rectangle pos = getPos();

	animations->draw(pos, frame, abs((int)state), (int)state < 0 ? true : false);
	if (IsKeyDown(KEY_TAB))
		Collider::draw(this);
}

void Player::drawInterface()
{
	eq->draw(IsKeyDown(KEY_ONE));
}