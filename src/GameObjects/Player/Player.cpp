#include "Player.h"
#include <math.h>
#include <iostream>
#include "../../core/Scenes/GameScene.h"
#include "../Projectals/Projectal.h"
#include "../ItemFactory.h"

Player::Player(Player& obj) :GameObject(obj), Collider(obj)
{
	animations = new AnimationController(*obj.animations);
	miniMap = new MiniMap(this);
	eq = new Eq();
}

Player::Player():GameObject({ 3000,3000,64,64 },"Player"), Collider({pos.width / 3,pos.height / 4,pos.width / 3,pos.width / 2})
{
	speed = 2;
	int n = 6;
	std::string names[6] = { "IDE","MoveUp","MoveDown","MoveLeft","Doge","Die" };
	std::vector<SpriteController*> sprites;
	for (int i = 0; i < n; i++)
	{
		std::string path = "Resource/Player/" + names[i] + ".png";
		sprites.push_back(new SpriteController(path.c_str()));
	}
	animations = new AnimationController(sprites);
	miniMap = new MiniMap(this);
	eq = new Eq();
}
Player::~Player()
{
	if(Game!=NULL)
		Game->removeUserUI(this);
	delete animations;
	delete miniMap;
}

void Player::start()
{
	Game->addUserUI(this);
	miniMap->generateMiniMap();
}

void Player::update()
{
	eq->update();
	move();
	eq->updateItemPos({ pos.x + pos.width / 2,pos.y + pos.height / 2 });
	Rectangle pos = getPos();
	pos.x -= pickUpRange;
	pos.y -= pickUpRange;
	pos.width += pickUpRange * 2;
	pos.height += pickUpRange * 2;
	std::list<GameObject*> objs = Game->getObjects(pos, ObjectToGet::getNoBlocks);
	for (GameObject* obj : objs)
	{
		if (obj->getType() != ObjectType::Item)
			continue;
		Item* item = dynamic_cast<Item*>(obj);
		if (item != NULL)
		{
			Rectangle myPos = getPos();
			Rectangle itemPos = item->getPos();
			if (CheckCollisionRecs(myPos, itemPos))
			{
				if (eq->addItem(item))
					Game->deleteObject(obj);
			}
			else
			{
				Vector2 moveTo = { myPos.x - itemPos.x,myPos.y - itemPos.y };
				float lenght = abs(moveTo.x) + abs(moveTo.y);
				moveTo.x /= lenght/2;
				moveTo.y /= lenght/2;
				item->addToPos(moveTo);
			}
		}



	}
	Game->updatePos(this);
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
			{
				state = playerAnimationState::MoveRight;
				eq->setFaceSide(FaceSide::right);
			}
			else
			{
				state = playerAnimationState::MoveLeft;
				eq->setFaceSide(FaceSide::left);
			}
				
		}
		if (posTmp.y != 0)
		{
			if (posTmp.y > 0)
			{
				state = playerAnimationState::MoveDown;
				eq->setFaceSide(FaceSide::down);
			}
			else
			{
				state = playerAnimationState::MoveUp; 
				eq->setFaceSide(FaceSide::up);
			}

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
	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		eq->pressOnEq();
	}
	if (GetMouseWheelMove() != 0)
		eq->mouseWeel();
	if (IsKeyPressed(KEY_I))
		eq->swapEqLook();

}
#define changePos {int s=6;pos.x += s;pos.y += s;pos.width -= s+s;pos.height -= s+s; }
void Player::draw()
{
	Rectangle pos = getPos();

	animations->draw(pos, frame, abs((int)state), (int)state < 0 ? true : false);
	if (IsKeyDown(KEY_TAB))
	{
		Rectangle posPickUpRange = getPos();
		posPickUpRange.x -= pickUpRange;
		posPickUpRange.y -= pickUpRange;
		posPickUpRange.width += pickUpRange * 2;
		posPickUpRange.height += pickUpRange * 2;
		Collider::draw(this);
		DrawRectangleRec(posPickUpRange, { 0,0,255,126 });
	}

	eq->drawItem();
}

void Player::drawInterface()
{
	eq->draw();
	miniMap->draw();
}