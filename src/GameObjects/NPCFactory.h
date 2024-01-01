#pragma once
#include "Factory.h"
#include "NPCs/NPC.h"
class NPCFactory :
	public Factory
{
	static NPCFactory* factory;
	std::vector<NPC*> objects;
	NPCFactory();
	~NPCFactory();
public:
	static NPCFactory* getFactory();

	void clearFactory();

	NPC* getObject(int ID);

	int getSize() { return objects.size(); }
};