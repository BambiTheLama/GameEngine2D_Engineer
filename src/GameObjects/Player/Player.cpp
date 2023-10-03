#include "Player.h"
#include <math.h>
#include <iostream>
#include "../../core/Scenes/GameScene.h"
#include "../Projectals/Projectal.h"
#include "../ItemFactory.h"


Player::Player(Player& obj) :GameObject(obj), RectangleCollider(obj),HitAble(obj)
{
	animations = new AnimationController(*obj.animations);
	miniMap = new MiniMap(this);
	eq = new Eq(this);
	crafting = new CraftingStation(CraftingStationEnum::NON);

}

Player::Player():GameObject({ 100,100,64,64 },"Player"), RectangleCollider({pos.width / 3,pos.height / 4,pos.width / 3,pos.width / 2}),HitAble(69)
{
	speed = 8;
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
	eq = new Eq(this);
	crafting = new CraftingStation(CraftingStationEnum::NON);
	
	for (int i = 0; i < Items->getSize(); i++)
	{
		Item* item= Items->getObject(i);
		eq->addItem(item);
		delete item;
	}
		

}


Player::~Player()
{
	if(Game)
		Game->removeUserUI(this);
	delete animations;
	delete miniMap;
	delete crafting;
	delete eq;
}

void Player::start()
{
	Game->addUserUI(this);
	miniMap->generateMiniMap();
}

void Player::pickUpItemsClose(float deltaTime)
{
	bool haveSpace = !eq->isFullEq();
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
		
		if (item == NULL)
			continue;
		if (!haveSpace && !item->isStacable())
			continue;
		if (!haveSpace && !eq->canTakeItem(item))
			continue;
		Rectangle myPos = getPos();
		myPos.x += myPos.width / 2;
		myPos.y += myPos.height / 2;
		myPos.width = 2;
		myPos.height = 2;
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
			moveTo.x /= lenght / (2*deltaTime * 64);
			moveTo.y /= lenght / (2*deltaTime * 64);
			item->addToPos(moveTo);
		}
		
	}
}

void Player::updateRecepies()
{
	std::vector<Item*> items = eq->getItems();
	crafting->updateItemsICanCraft(items);
}

void Player::updateCrafting()
{
	if (IsKeyPressed(KEY_F1))
		crafting->swapItemsSee();


	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		if (crafting->isPressedCraft())
		{
			if (!eq->canAddItemToHand(crafting->isStacableItem(), crafting->getItemID(), crafting->getStackSize()))
				return;

			Item* item = crafting->craftItem(eq->getAllItems(), EqWight, EqHeight);
			if (item)
			{
				eq->addItemToHand(item);

			}
			

		}

	}
	else if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
	{
		if (crafting->isPressedCraft())
		{
			Item* item = crafting->craftItem(eq->getAllItems(), EqWight, EqHeight);
			if (item)
			{
				if (!eq->addItem(item))
				{
					Game->addObject(item);
					item->setMovePos({ pos.x + pos.width / 2,pos.y + pos.height / 2 });
				}

			}

		}
	}
}

void Player::updateEq(float deltaTime)
{
	eq->update(deltaTime);
	eq->updateItemPos({ pos.x + pos.width / 2,pos.y + pos.height / 2 });
	if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
	{
		if (!eq->isPressedOnEq() &&!crafting->isPressedInCraftingUI())
			eq->useItem(deltaTime);
		else
			eq->endUsingItem();
	}
	else if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
	{
		eq->endUsingItem();
	}
	if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON) && !eq->isPressedOnEq())
		eq->dropItemFromHand();
	if (GetMouseWheelMove() != 0)
		eq->mouseWeel();
	if (IsKeyPressed(KEY_I))
	{
		eq->swapEqLook();
		crafting->swapVisibility();
		updateRecepies();
	}

	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		eq->updateEqPressed();

	if (IsKeyPressed(KEY_F2))
		eq->sortItems(sortBy::ID);
	if (IsKeyPressed(KEY_F3))
		eq->sortItems(sortBy::NAME);
	if (IsKeyPressed(KEY_F4))
		eq->sortItems(sortBy::Type);
	eq->update(0.0);
}

void Player::update(float deltaTime)
{
	move(deltaTime);
	Game->updatePos(this);
	updateEq(deltaTime);
	pickUpItemsClose(deltaTime);
	updateCrafting();
	HitAble::update(deltaTime);
}

void Player::move(float deltaTime)
{
	
	Vector2 posTmp = { 0,0 };
	if (canMove)
	{
		if (IsKeyDown(KEY_A))
		{
			posTmp.x -= 1;
		}
		if (IsKeyDown(KEY_D))
		{
			posTmp.x += 1;
		}
		if (IsKeyDown(KEY_W))
		{
			posTmp.y -= 1;
		}
		if (IsKeyDown(KEY_S))
		{
			posTmp.y += 1;
		}
		if (eq->canChangeItem())
		{
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
		}

		if (IsKeyDown(KEY_SPACE))
		{
			state = playerAnimationState::Doge;
		}
	}
	posTmp.x *= speed * 64.0f * deltaTime;
	posTmp.y *= speed * 64.0f * deltaTime;
	Rectangle pos = getPos();
	setMovePos({ posTmp.x + pos.x, pos.y + posTmp.y });
	if (isCollidingWithSomething())
	{
		setMovePos({ pos.x, pos.y });
	}
}

void Player::draw()
{
	Rectangle pos = getPos();

	animations->draw(pos, frame, abs((int)state), (int)state < 0 ? true : false);
	if (collidersToDraw)
	{
		Rectangle posPickUpRange = getPos();
		posPickUpRange.x -= pickUpRange;
		posPickUpRange.y -= pickUpRange;
		posPickUpRange.width += pickUpRange * 2;
		posPickUpRange.height += pickUpRange * 2;
		DrawRectangleRec(posPickUpRange, { 0,0,255,126 });
		RectangleCollider::draw(this);
		DrawTextWithOutline(TextFormat("(%d:%d)", getChunkX(), getChunkY()), pos.x, pos.y, textStandardSize, WHITE, BLACK);
	}
	HitAble::draw({pos.x,pos.y+pos.height,pos.width,20});
	eq->drawItem();
}

void Player::drawInterface()
{
	//miniMap->draw();
	crafting->draw();
	eq->draw();
}