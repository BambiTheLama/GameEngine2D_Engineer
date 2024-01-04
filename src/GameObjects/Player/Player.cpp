#include "Player.h"
#include <math.h>
#include <iostream>
#include "../../core/Scenes/GameScene.h"
#include "../Projectals/Projectal.h"
#include "../ItemFactory.h"


Player::Player(Player& obj) :GameObject(obj), RectangleCollider(obj),HitAble(obj)
{
	miniMap = new MiniMap(this);
	eq = new Eq(this);
	crafting = new CraftingStation(CraftingStationEnum::NON);
	body = new CharacterBody(*obj.body);
}

Player::Player() :GameObject({ 100,100,48,80 }, "Player")
, RectangleCollider({ 12,22,24,58 })
, HitAble(69)
{
	speed = 8;
	miniMap = new MiniMap(this);
	eq = new Eq(this);
	crafting = new CraftingStation(CraftingStationEnum::NON);
	
	for (int i = 0; i < Items->getSize(); i++)
	{
		Item* item= Items->getObject(i);
		eq->addItem(item);
		delete item;
	}
	Rectangle pos = getPos();
	body = new CharacterBody("Resource/Character/Character_1/",pos.width,pos.width);

}


Player::~Player()
{
	if(Game)
		Game->removeUserUI(this);
	delete body;
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
	eq->updateItemPos(body->getHandPos());
	eq->update(deltaTime);
	//eq->updateItemPos({ pos.x + pos.width / 2,pos.y + pos.height / 2 });
	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		Vector2 mousePos = Game->getCursorPos();
		if (!interactObject)
		{

			std::list <GameObject*> objs = Game->getObjects({ mousePos.x,mousePos.y,1,1 }, ObjectToGet::getNoBlocks);
			for (auto o : objs)
			{
				if (o->getType() != ObjectType::NPC)
					continue;
				interactObject = o;
				shop = dynamic_cast<Shop*>(o);
				eq->setEqFullLook();		
				crafting->setVisibility(true);
			}
		}
		else
		{
			Item* i = shop->updateShop(Game->worldToScreanPos(mousePos), shopX, shopY, money);
			
			if (i && !eq->addItem(i))
			{
				Rectangle pos = getPos();
				i->setMovePos({ pos.x + pos.width / 2, pos.y + pos.height / 2 });
				Game->addObject(i);
			}
		}
	}
	else if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
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
		crafting->setVisibility(eq->isFullEqVisuble());
		updateRecepies();
		if (shop)
			shop = NULL;
		interactObject = NULL;
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
	if (interactObject)
	{
		Rectangle pos = getPos();
		Vector2 p1 = { pos.x + pos.width / 2,pos.y + pos.height / 2 };
		pos = interactObject->getPos();
		Vector2 p2 = { pos.x + pos.width / 2,pos.y + pos.height / 2 };
		float len = sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2)*1.6);
		if (len > 200)
		{
			shop = NULL;
			interactObject = NULL;
		}
	}

}

void Player::update(float deltaTime)
{
	if (IsKeyPressed(KEY_F4))
		alive = !alive;
	if (alive)
	{

		move(deltaTime);
		Game->updatePos(this);
		updateEq(deltaTime);
		pickUpItemsClose(deltaTime);
		updateCrafting();
		HitAble::update(deltaTime);
		
	}
	else
	{
		body->updateCharacterState(CharacterState::Die);
	}
	body->update(deltaTime, Game->getCursorPos(),getPos());

}

void Player::move(float deltaTime)
{
	bool moving = false;
	Vector2 posTmp = { 0,0 };
	if (canMove)
	{
		if (IsKeyDown(KEY_A))
		{
			posTmp.x -= 1;
			moving = true;
		}
		if (IsKeyDown(KEY_D))
		{
			posTmp.x += 1;
			moving = true;
		}
		if (IsKeyDown(KEY_W))
		{
			posTmp.y -= 1;
			moving = true;
		}
		if (IsKeyDown(KEY_S))
		{
			posTmp.y += 1;
			moving = true;
		}
		if (eq->canChangeItem())
		{
			if (posTmp.x != 0)
			{

				if (posTmp.x > 0)
				{
					body->updateCharacterSide(CharacterSide::Right);
				}
				else
				{
					body->updateCharacterSide(CharacterSide::Left);
				}

			}
			if (posTmp.y != 0)
			{

				if (posTmp.y > 0)
				{
					body->updateCharacterSide(CharacterSide::Down);
				}
				else
				{
					body->updateCharacterSide(CharacterSide::Up);
				}

			}
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
	if(moving)
		body->updateCharacterState(CharacterState::Run);
	else
		body->updateCharacterState(CharacterState::Ide);
}

void Player::draw()
{
	Rectangle pos = getPos();
	//DrawRectangleRec(pos, { 0,0,255,122 });
	body->draw(pos);
	
	if (collidersToDraw)
	{
		Rectangle posPickUpRange = getPos();
		posPickUpRange.x -= pickUpRange;
		posPickUpRange.y -= pickUpRange;
		posPickUpRange.width += pickUpRange * 2;
		posPickUpRange.height += pickUpRange * 2;
		//DrawRectangleRec(posPickUpRange, { 0,0,255,126 });
		RectangleCollider::draw(this);
		DrawTextWithOutline(TextFormat("(%d:%d)", getChunkX(), getChunkY()), pos.x, pos.y, textStandardSize, WHITE, BLACK);
	}
	//HitAble::draw({pos.x,pos.y+pos.height,pos.width,20});
	eq->drawItem();

}

void Player::drawInterface()
{
	eq->drawItemInterface();
	crafting->draw();
	eq->draw();
	const char* text = TextFormat("%d$", money);
	int screenW = GetScreenWidth() - textSize(text, textStandardSize).x - 10;

	DrawTextWithOutline(text, screenW, 10, textStandardSize, YELLOW, BLACK);
	if (shop)
		shop->drawShop(shopX, shopY);
}

void Player::saveToJson(nlohmann::json& writer)
{
	GameObject::saveToJson(writer);
	HitAble::saveToJson(writer);
	eq->saveData(writer);
	body->saveData(writer);
	writer["PickUpRange"] = pickUpRange;
	writer["Speed"] = speed;
	writer["Alive"] = alive;
	writer["Money"] = money;
}

void Player::readFromJson(nlohmann::json& reader)
{
	GameObject::readFromJson(reader);
	HitAble::readFromJson(reader);
	eq->readData(reader);
	body->readData(reader);
	if(reader.contains("PickUpRange"))
		pickUpRange = reader["PickUpRange"];
	if (reader.contains("Speed"))
		speed = reader["Speed"];
	if (reader.contains("Alive"))
		alive = reader["Alive"];
	if (reader.contains("Money"))
		money = reader["Money"];

}