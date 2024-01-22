#pragma once
#include "Blocks/Block.h"
#include <vector>
#include "Factory.h"
#define Blocks BlockFactory::getFactory()

enum class BlockID
{
	Water=0,
	Sand,
	Grass,
	Dirt,
	Stone,
	Snow,
	Ice,
	Hole,

};

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

	Block* getObject(int ID);

	Block* getObject(BlockID ID);

	int getSize() { return objects.size(); }
};

