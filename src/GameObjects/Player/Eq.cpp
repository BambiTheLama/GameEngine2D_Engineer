#include "Eq.h"
#include <vector>

Eq::Eq()
{
	for (int i = 0; i < EqHeight; i++)
		for (int j = 0; j < EqWight; j++)
			items[i][j] = NULL;
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
	for (int i = 0; i < EqHeight; i++)
		for (int j = 0; j < EqWight; j++)
		{
			if (items[i][j] == NULL)
			{
				items[i][j] = item;
				return true;
			}
		}

	return false;
}

bool Eq::useItem()
{
	return false;
}

void Eq::draw(bool fullEq)
{
	for (int i = 0; i < (fullEq ? EqHeight : 1); i++)
		for (int j = 0; j < EqWight; j++)
		{
			Rectangle posToDraw = { EqStartX + (EqSpacing + EqSize) * j - EqSpacing,
				EqStartY + (EqSpacing + EqSize) * i - EqSpacing, EqSize, EqSize };
			DrawRectangleRec(posToDraw, RED);

		}
}