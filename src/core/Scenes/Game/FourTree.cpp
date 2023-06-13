#include "FourTree.h"
#include <algorithm>


FourTree::FourTree(Rectangle pos)
{
	this->pos = pos;
}
FourTree::~FourTree()
{
	if (tree != NULL)
		closeTree();

}
void FourTree::addObj(GameObject* obj)
{
	if (hasObj(obj)) return;

	if (!CheckCollisionRecs(obj->getPos(), pos)) return;

	objects.push_back(obj);
	if (tree == NULL)
	{
		if ((pos.width >256 || pos.height > 256) && objects.size() > 10)
			openTree();
	}
	else
	{
		for(int i=0;i<4;i++)
			if (CheckCollisionRecs(pos, tree[i]->pos))
			{
				tree[i]->addObj(obj);
			}
	}
}
void FourTree::removeObj(GameObject* obj)
{
	if (!hasObj(obj)) return;
	
	objects.remove(obj);

	if (tree == NULL) return;

	for (int i = 0; i < 4; i++)
		tree[i]->removeObj(obj);
	if (objects.size() < 3)
	{
		closeTree();
	}
}
void FourTree::openTree()
{
	tree = new FourTree * [4];
	float w = pos.width / 2;
	float h = pos.height / 2;
	tree[0] = new FourTree({ pos.x,pos.y,w,h });
	tree[1] = new FourTree({ pos.x + w,pos.y,w,h });
	tree[2] = new FourTree({ pos.x + w,pos.y + h,w,h });
	tree[3] = new FourTree({ pos.x,pos.y + h,w,h });
}
void FourTree::closeTree()
{
	for (int i = 0; i < 4; i++)
		delete tree[i];
	delete tree;
	tree = NULL;
}
void FourTree::updatePos(GameObject* obj)
{
	bool collision = CheckCollisionRecs(obj->getPos(), pos);
	bool has = hasObj(obj);
	if (collision)
	{
		if (has)
		{
			allTreeIf->updatePos(obj);
		}
		else
		{
			addObj(obj);
		}
		return;

	}
	else
	{
		if (has)
		{
			removeObj(obj);
		}
			
		return;
	}
	
}

bool FourTree::hasObj(GameObject* obj)
{
	//return listHas(objects, obj);
	for (allObjects)
		if (o == obj)
			return true;
	return false;

}

void FourTree::getObjectsAt(Rectangle pos, std::list<GameObject*>& objs)
{
	if (tree != NULL)
	{
		for (int i = 0; i < 4; i++)
			if (CheckCollisionRecs(pos, tree[i]->pos))
				tree[i]->getObjectsAt(pos, objs);
		return;
	}
	for(allObjects)
		if (CheckCollisionRecs(pos, o->getPos()) )
		{
			bool has = false;
			for (GameObject* obj : objs)
				if (obj == o)
				{
					has = true;
					break;
				}
					
			if(!has)
				objs.push_back(o);
		}
			
}

std::list<GameObject*> FourTree::getObjectsAt(Rectangle pos)
{
	std::list<GameObject*> objs;
	if (CheckCollisionRecs(pos, this->pos))
		getObjectsAt(pos, objs);

	return objs;

}