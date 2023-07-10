#pragma once
#include "Blocks/Block.h"
#include <vector>
#include "Factory.h"

#define Blocks BlockFactory::getFactory()
class BlockFactory
	:public Factory
{
	static BlockFactory* factory;
	std::vector<Block*> objects;
	BlockFactory();
	~BlockFactory();
public:
	static BlockFactory* getFactory();

	void clearFactory();

	Block* getObject(int i);

	int getSize() { return objects.size(); }
};

