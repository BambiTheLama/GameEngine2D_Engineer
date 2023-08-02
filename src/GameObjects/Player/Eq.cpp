#include "Eq.h"
#include <vector>
#include "../ItemFactory.h"
Eq::Eq()
{
	items = new Item * *[EqHeight];
	for (int i = 0; i < EqHeight; i++)
	{
		items[i] = new  Item * [EqWight];
		for (int j = 0; j < EqWight; j++)
			items[i][j] = Items->getObject(i * EqWight + j);
	}

}

Eq::~Eq()
{
	for (int i = 0; i < EqHeight; i++)
	{
		for (int j = 0; j < EqWight; j++)
			if (items[i][j] != NULL)
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
			if (items[i][j] != NULL)
			{
				itemsTmp.push_back(items[i][j]);
				items[i][j] = NULL;
			}
		}
	if (sortBy::ID == type)
	{
		for (int i = 0; i < itemsTmp.size(); i++)
		{

			for (int j = 0; j < itemsTmp.size() / 2; j++)
			{
				if (itemsTmp[j]->getID() > itemsTmp[j + 1]->getID())
				{
					Item* tmp = itemsTmp[j];
					itemsTmp[j] = itemsTmp[j + 1];
					itemsTmp[j + 1] = tmp;
				}
				int n = itemsTmp.size() - 1 - j;
				if (itemsTmp[n - 1]->getID() > itemsTmp[n]->getID())
				{
					Item* tmp = itemsTmp[n];
					itemsTmp[n] = itemsTmp[n - 1];
					itemsTmp[n - 1] = tmp;
				}

			}
		}
	}


	for (int i = 0; i < itemsTmp.size(); i++)
	{
		items[1 + (i) / 10][i % 10] = itemsTmp[i];
	}
}

bool Eq::addItem(Item* item)
{
	if (item->isStacable())
	{
		for (int i = 0; i < EqHeight; i++)
			for (int j = 0; j < EqWight; j++)
			{
				if (items[i][j] != NULL && items[i][j]->addToStack(item))
					return true;
			}
	}



	for (int i = 0; i < EqHeight; i++)
		for (int j = 0; j < EqWight; j++)
		{
			if (items[i][j] == NULL)
			{
				items[i][j] = item->clone();
				return true;
			}
		}

	return false;
}

bool Eq::useItem()
{
	return false;
}
void Eq::updateItemPos(Vector2 movePos)
{ 
	if (items[usingItemY][usingItemX] != NULL) 
		items[usingItemY][usingItemX]->setMovePos(movePos);;
}

void Eq::update()
{
	usingItemX = usingItem % EqWight;
	usingItemY = usingItem / EqWight;
	if (items[usingItemY][usingItemX] != NULL)
	{
		items[usingItemY][usingItemX]->update();
		items[usingItemY][usingItemX]->setFaceSide(faceSide);
		if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
			items[usingItemY][usingItemX]->use();
	}
}

void Eq::mouseWeel()
{
	usingItem = (int)(EqWight + usingItem + GetMouseWheelMove()) % EqWight;
}



void Eq::pressOnEq()
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
				return;
			if ((int)cursor.y % (EqSize + EqSpacing) > EqSize)
				return;
			int x = cursor.x / (EqSize + EqSpacing);
			int y = cursor.y / (EqSize + EqSpacing);

			if (items[y][x] != NULL && itemInHand != NULL && items[y][x]->getID() == itemInHand->getID())
			{
				if (items[y][x]->addToStack(itemInHand))
				{
					delete itemInHand;
					itemInHand = NULL;
				}
			}
			else
			{
				Item* i = items[y][x];
				items[y][x] = itemInHand;
				itemInHand = i;
			}



			usingItem = x + y * EqWight;

		}

	}
}

void Eq::draw()
{
	for (int i = 0; i < (fullEq ? EqHeight : 1); i++)
		for (int j = 0; j < EqWight; j++)
		{
			Rectangle posToDraw = { EqStartX + (EqSpacing + EqSize) * j - EqSpacing,
				EqStartY + (EqSpacing + EqSize) * i - EqSpacing, EqSize, EqSize };

			DrawRectangleRec(posToDraw, usingItem == i * EqWight + j ? BLUE : RED);
			if (items[i][j] != NULL)
			{
				items[i][j]->drawAt(posToDraw);
				if (items[i][j]->isStacable())
				{
					const char* text = TextFormat("%d", items[i][j]->getStackSize());
					Vector2 textS = textSize(text, textStandardSize);
					drawText(text, posToDraw.x + posToDraw.height- textS.x, posToDraw.y + posToDraw.width - textS.y, textStandardSize, BLACK);
				}
			}

			drawText(TextFormat("%d", i * EqWight + j), posToDraw.x, posToDraw.y, textStandardSize, BLACK);

		}
	if (itemInHand != NULL)
	{
		Vector2 mouse = GetMousePosition();
		Rectangle pos = { mouse.x,mouse.y,32,32 };
		DrawRectangleRec(pos, BLUE);
		itemInHand->drawAt(pos);
		if(itemInHand->isStacable())
		{
			const char* text = TextFormat("%d", itemInHand->getStackSize());
			Vector2 textS = textSize(text, textStandardSize);
			drawText(text, pos.x + pos.height - textS.x, pos.y + pos.width - textS.y, textStandardSize, BLACK);
		}
	}
}

void Eq::drawItem()
{
	if (items[usingItemY][usingItemX] != NULL)
	{
		items[usingItemY][usingItemX]->draw();
	}
}


std::vector<Item*> Eq::getItems()
{
	std::vector<Item*> itemsToRet;

	for(int i=0;i<EqHeight;i++)
		for (int j = 0; j < EqWight; j++)
		{
			if (items[i][j] != NULL)
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
		return;
	}
	itemInHand->addToStack(item);
	delete item;
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
			if (items[i][j] != NULL && items[i][j]->getID() == item->getID())
			{
				if (items[i][j]->getStackSize() < items[i][j]->getStackMaxSize())
					return true;
			}
				
	return false;
}