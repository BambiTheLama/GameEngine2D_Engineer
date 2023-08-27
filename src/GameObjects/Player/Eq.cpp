#include "Eq.h"
#include <vector>
#include "../ItemFactory.h"
#include "Player.h"

Eq::Eq(Player* player)
{
	items = new Item * *[EqHeight];
	for (int i = 0; i < EqHeight; i++)
	{
		items[i] = new  Item * [EqWight];
		for (int j = 0; j < EqWight; j++)
			items[i][j] = NULL;
	}

	this->player = player;
}

Eq::~Eq()
{
	for (int i = 0; i < EqHeight; i++)
	{
		for (int j = 0; j < EqWight; j++)
			if (items[i][j])
				delete items[i][j];
		delete items[i];
	}
	delete items;

}

void Eq::sortItems(sortBy type)
{
	std::vector<Item*> itemsTmp;

	for (int i = 1; i < EqHeight; i++)
		for (int j = 0; j < EqWight; j++)
		{
			if (items[i][j])
			{
				itemsTmp.push_back(items[i][j]);
				items[i][j] = NULL;
			}
		}
	if (sortBy::ID == type)
	{
		for (int i = 0; i < itemsTmp.size(); i++)
		{
			for (int j = 0; j < itemsTmp.size()-1; j++)
			{
				if (itemsTmp[j]->getID() > itemsTmp[j + 1]->getID())
				{
					Item* tmp = itemsTmp[j];
					itemsTmp[j] = itemsTmp[j + 1];
					itemsTmp[j + 1] = tmp;
				}
			}
		}
	}
	else if (sortBy::NAME == type)
	{
		for (int i = 0; i < itemsTmp.size(); i++)
		{

			for (int j = 0; j < itemsTmp.size() -1; j++)
			{
				int compare = itemsTmp[j]->getName().compare(itemsTmp[j + 1]->getName());
				if (compare>0)
				{
					Item* tmp = itemsTmp[j];
					itemsTmp[j] = itemsTmp[j + 1];
					itemsTmp[j + 1] = tmp;
				}
			}
		}
	}


	for (int i = 0; i < itemsTmp.size(); i++)
	{
		addItem(itemsTmp[i]);
	}
}

bool Eq::addItem(Item* item)
{
	if (item->isStacable())
	{
		for (int i = EqHeight - 1; i >= 0; i--)
			for (int j = EqWight - 1; j >= 0; j--)
			{
				if (items[i][j] && items[i][j]->addToStack(item))
				{
					player->updateRecepies();

					return true;
				}

			}

		player->updateRecepies();
	}



	for (int i = EqHeight - 1; i >= 0; i--)
		for (int j = EqWight - 1; j >= 0; j--)
		{
			if (items[i][j] == NULL)
			{
				items[i][j] = item->clone();
				items[i][j]->setEq(this);
				items[i][j]->setInHand(true);
				player->updateRecepies();
				return true;
			}
		}

	return false;
}

bool Eq::useItem(float deltaTime)
{
	if (itemInHand)
	{
		return itemInHand->use(deltaTime);
	}
	if (items[usingItemY][usingItemX])
	{
		return items[usingItemY][usingItemX]->use(deltaTime);
	}
	return false;
}

void Eq::updateItemPos(Vector2 movePos)
{ 
	if (itemInHand)
		itemInHand->setMovePos(movePos);
	else if (items[usingItemY][usingItemX]) 
		items[usingItemY][usingItemX]->setMovePos(movePos);;
}

void Eq::update(float deltaTime)
{
	if (itemInHand)
	{
		itemInHand->update(deltaTime);
		itemInHand->setFaceSide(faceSide);
	}
	else
	{
		usingItemX = usingItem % EqWight;
		usingItemY = usingItem / EqWight;
		if (items[usingItemY][usingItemX])
		{
			items[usingItemY][usingItemX]->update(deltaTime);
			items[usingItemY][usingItemX]->setFaceSide(faceSide);
		}
	}
}

void Eq::mouseWeel()
{
	if (items[usingItemY][usingItemX] == NULL || items[usingItemY][usingItemX]->canChangeItem())
	{
		usingItem = (int)(EqWight + usingItem + GetMouseWheelMove()) % EqWight;
		changeItem();

	}

}

bool Eq::isPressedOnEq()
{
	Vector2 cursor = GetMousePosition();
	cursor.x -= EqStartX - EqSpacing;
	int endX = EqSize * EqWight + EqSpacing * (EqWight - 1);
	if (cursor.x >= 0 && cursor.x <= endX)
	{
		cursor.y -= EqStartY - EqSpacing;
		int endY;
		if (fullEq)
			endY = EqSize * EqHeight + EqSpacing * (EqHeight - 1);
		else
			endY = EqSize;
		
		if (cursor.y >= 0 && cursor.y <= endY)
		{
			if ((int)cursor.x % (EqSize + EqSpacing) > EqSize)
				return false;
			if ((int)cursor.y % (EqSize + EqSpacing) > EqSize)
				return false;

			return true;
		}

	}
	return false;
}

void Eq::updateEqPressed()
{
	if (!isPressedOnEq())
		return;
	if (items[usingItemY][usingItemX] && !items[usingItemY][usingItemX]->canChangeItem())
		return;
	Vector2 cursor = GetMousePosition();
	cursor.x -= EqStartX - EqSpacing;
	cursor.y -= EqStartY - EqSpacing;
	int x = cursor.x / (EqSize + EqSpacing);
	int y = cursor.y / (EqSize + EqSpacing);

	if (items[y][x] && itemInHand && items[y][x]->getID() == itemInHand->getID())
	{
		if (items[y][x]->addToStack(itemInHand))
		{
			delete itemInHand;
			itemInHand = NULL;
			player->updateRecepies();
		}
	}
	else
	{
		Item* i = items[y][x];
		items[y][x] = itemInHand;
		itemInHand = i;
		player->updateRecepies();
	}
	usingItem = x + y * EqWight;
	changeItem();
}

void Eq::draw()
{
	for (int i = 0; i < (fullEq ? EqHeight : 1); i++)
		for (int j = 0; j < EqWight; j++)
		{
			Rectangle posToDraw = { EqStartX + (EqSpacing + EqSize) * j - EqSpacing,
				EqStartY + (EqSpacing + EqSize) * i - EqSpacing, EqSize, EqSize };

			DrawRectangleRec(posToDraw, usingItem == i * EqWight + j ? BLUE : RED);
			if (items[i][j])
			{
				items[i][j]->drawAt(posToDraw);
				if (items[i][j]->isStacable())
				{
					const char* text = TextFormat("%d", items[i][j]->getStackSize());
					Vector2 textS = textSize(text, textStandardSize);
					DrawTextWithOutline(text, posToDraw.x + posToDraw.height - textS.x, posToDraw.y + posToDraw.width - textS.y, textStandardSize, WHITE, BLACK);
				}
			}
			DrawTextWithOutline(TextFormat("%d", i * EqWight + j), posToDraw.x, posToDraw.y, textStandardSize, WHITE, BLACK);
		}
	if (itemInHand)
	{
		Vector2 mouse = GetMousePosition();
		Rectangle pos = { mouse.x,mouse.y,32,32 };
		DrawRectangleRec(pos, BLUE);
		itemInHand->drawAt(pos);
		if(itemInHand->isStacable())
		{
			const char* text = TextFormat("%d", itemInHand->getStackSize());
			Vector2 textS = textSize(text, textStandardSize);
			DrawTextWithOutline(text, pos.x + pos.height - textS.x, pos.y + pos.width - textS.y, textStandardSize, WHITE, BLACK);
		}
	}
}

void Eq::drawItem()
{
	if (itemInHand)
		itemInHand->draw();
	else if (items[usingItemY][usingItemX])
		items[usingItemY][usingItemX]->draw();
}

std::vector<Item*> Eq::getItems()
{
	std::vector<Item*> itemsToRet;

	for(int i=0;i<EqHeight;i++)
		for (int j = 0; j < EqWight; j++)
		{
			if (items[i][j])
				itemsToRet.push_back(items[i][j]);
		}

	return itemsToRet;
}

bool Eq::canAddItemToHand(bool stacable, int ID, int stackSize)
{
	if (itemInHand == NULL)
		return true;
	if (stacable && itemInHand->getID() == ID)
		if (itemInHand->getStackMaxSize() - itemInHand->getStackSize() >= stackSize)
			return true;

	return false;
}

void Eq::addItemToHand(Item* item)
{
	if (itemInHand == NULL)
	{
		itemInHand = item;
		itemInHand->setEq(this);
		itemInHand->setInHand(false);
		player->updateRecepies();
		return;
	}
	if(itemInHand->addToStack(item))
		delete item;
	player->updateRecepies();
}

bool Eq::isFullEq()
{
	for (int i = 0; i < EqHeight; i++)
		for (int j = 0; j < EqWight; j++)
			if (items[i][j] == NULL)
				return false;
	return true;
}

bool Eq::canTakeItem(Item* item)
{
	if (!item->isStacable())
		return false;
	for (int i = 0; i < EqHeight; i++)
		for (int j = 0; j < EqWight; j++)
			if (items[i][j] && items[i][j]->getID() == item->getID())
			{
				if (items[i][j]->getStackSize() < items[i][j]->getStackMaxSize())
					return true;
			}
				
	return false;
}

void Eq::dropItemFromHand()
{
	if (itemInHand == NULL)
		return;
	if (!itemInHand->canChangeItem())
		return;
	Game->addObject(itemInHand);
	Vector2 cursor = Game->getCursorPos();
	itemInHand->setInHand(false);
	itemInHand->setMovePos(cursor);
	itemInHand->setEq(NULL);
	itemInHand = NULL;
}

bool Eq::canChangeItem()
{
	if (itemInHand == NULL)
	{
		if (items[usingItemY][usingItemX] == NULL)
			return true;
		else
			return items[usingItemY][usingItemX]->canChangeItem();
	}
	return itemInHand->canChangeItem();
}

void Eq::endUsingItem()
{
	if (itemInHand)
	{
		itemInHand->endUsing();
	}
	else if (items[usingItemY][usingItemX])
	{
		items[usingItemY][usingItemX]->endUsing();
	}
}

void Eq::removeItem(Item* item)
{
	item->setEq(NULL);
	if (itemInHand == item)
		itemInHand = NULL;
	for (int i = 0; i < EqHeight; i++)
	{
		for (int j = 0; j < EqWight; j++)
		{
			if (items[i][j] == item)
			{
				items[i][j] = NULL;
			}
		}
	}
}

void Eq::changeItem()
{
	if (itemInHand == NULL)
	{
		usingItemX = usingItem % EqWight;
		usingItemY = usingItem / EqWight;
		if (items[usingItemY][usingItemX])
			items[usingItemY][usingItemX]->updateAfterSwap();
	}
	else
		itemInHand->updateAfterSwap();

}