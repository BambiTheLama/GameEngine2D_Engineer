#pragma once
#include <list>
#include "../../../GameObjects/GameObject.h"
#define allTreeIf if (tree) for (int i = 0; i < 4; i++)tree[i]
#define allTree	for (int i = 0; i < 4; i++)tree[i]
#define allObjects GameObject* o : objects


class FourTree
{
	Rectangle pos;
	std::list<GameObject*> objects;
	FourTree** tree = NULL;
	void getObjectsAt(Rectangle pos,std::list<GameObject*> &objs);
public:
	FourTree(Rectangle pos);
	~FourTree();
	void addObj(GameObject* obj);
	void removeObj(GameObject* obj);
	void openTree();
	void closeTree();
	void updatePos(GameObject* obj);
	bool hasObj(GameObject* obj);
	std::list<GameObject*> getObjectsAt(Rectangle pos);
	void draw();
};

