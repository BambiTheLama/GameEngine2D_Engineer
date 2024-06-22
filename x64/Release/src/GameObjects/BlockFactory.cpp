#include "BlockFactory.h"
#include "../core/Scenes/GameScene.h"
#include "Blocks/CollidingBlock.h"
BlockFactory* BlockFactory::factory=NULL;

BlockFactory::BlockFactory()
{
	//objects.push_back(new CollidingBlock({ 0,0,tileSize,tileSize }, ToolType::NON, 0 ,"Water"));
	objects.push_back(new Block({ 0,0,tileSize,tileSize }, ToolType::NON, 0, "Water"));
	objects.push_back(new Block({ 0,0,tileSize,tileSize }, ToolType::Shovel, 10 ,"Sand"));
	objects.push_back(new Block({ 0,0,tileSize,tileSize }, ToolType::Shovel, 20 ,"Grass"));
	objects.push_back(new Block({ 0,0,tileSize,tileSize }, ToolType::Shovel, 30 ,"Dirt"));
	objects.push_back(new Block({ 0,0,tileSize,tileSize }, ToolType::Pickaxe, 10 ,"Stone"));
	objects.push_back(new Block({ 0,0,tileSize,tileSize }, ToolType::Shovel, 10, "Snow"));
	objects.push_back(new Block({ 0,0,tileSize,tileSize }, ToolType::Pickaxe, 10, "Ice"));
	objects.push_back(new Block({ 0,0,tileSize,tileSize }, ToolType::NON, 0 ,"Hole"));

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
	factory = NULL;
	objects.clear();
	printf("[FactoryBlock]: Usuni�to fabryke blokow\n");
}

BlockFactory* BlockFactory::getFactory()
{
	if (factory == NULL)
		factory = new BlockFactory();
	return factory;
}

void BlockFactory::clearFactory()
{
	if (factory)
	{
		delete factory;
		factory = NULL;
	}
}

Block* BlockFactory::getObject(int i)
{
	if (i > -1 && i < objects.size())
		return objects[i]->clone();
	return NULL;
}

