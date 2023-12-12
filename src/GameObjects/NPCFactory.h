#pragma once
#include "Factory.h"
#include "NPCs/Enemy.h"
class NPCFactory :
    public Factory
{
    static NPCFactory* factory;
	std::vector<Enemy*> objects;
	NPCFactory();
	~NPCFactory();
public:
	static NPCFactory* getFactory();

	void clearFactory();

	Enemy* getObject(int ID);

	int getSize() { return objects.size(); }
};

