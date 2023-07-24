#include "BlockFactory.h"
#include "../core/Scenes/GameScene.h"
#include "Blocks/CollidingBlock.h"
BlockFactory* BlockFactory::factory=NULL;

BlockFactory::BlockFactory()
{
	objects.push_back(new CollidingBlock({ 0,0,tileSize,tileSize }, ToolType::NON, 0 ,"Water"));
	objects.push_back(new Block({ 0,0,tileSize,tileSize }, ToolType::Shovel, 0 ,"Sand"));
	objects.push_back(new Block({ 0,0,tileSize,tileSize }, ToolType::Shovel, 0 ,"Grass"));
	objects.push_back(new Block({ 0,0,tileSize,tileSize }, ToolType::Shovel, 0 ,"Dirt"));
	objects.push_back(new Block({ 0,0,tileSize,tileSize }, ToolType::Pickaxe, 0 ,"Stone"));


	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->ID = i;
	}
	printf("[FactoryBlock]: Stworzono fabryke blokow\n");
}

BlockFactory::~BlockFactory()
{
	for (Block* b : objects)
		delete b;
	objects.clear();
	printf("[FactoryBlock]: Usuniêto fabryke blokow\n");
}

BlockFactory* BlockFactory::getFactory()
{
	if (factory == NULL)
		factory = new BlockFactory();
	return factory;
}

void BlockFactory::clearFactory()
{
	if (factory != NULL)
		delete factory;
	factory = NULL;
}

Block* BlockFactory::getObject(int i)
{
	if (i > -1 && i < objects.size())
		return objects[i]->clone();
	return NULL;
}