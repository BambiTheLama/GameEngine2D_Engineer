#include "BlockFactory.h"
#include "../core/Scenes/GameScene.h"
#include "Blocks/CollidingBlock.h"
BlockFactory* BlockFactory::factory=NULL;

BlockFactory::BlockFactory()
{
	std::string path = "Resource/Blocks/";
	objects.push_back(new CollidingBlock({ 0,0,tileSize,tileSize }, ToolType::NON, 0, path + "Water.png"));

	objects.push_back(new Block({ 0,0,tileSize,tileSize }, ToolType::All, 0, path+"Dirt.png"));


	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->ID = i;
	}
}

BlockFactory::~BlockFactory()
{
	for (Block* b : objects)
		delete b;
	objects.clear();
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