#include "BlockFactory.h"
#include "../core/Scenes/GameScene.h"

BlockFactory* BlockFactory::factory=NULL;

BlockFactory::BlockFactory()
{
	objects.push_back(new Block({ 0,0,tileSize,tileSize }, ToolType::All, 0, BLACK));
	objects.push_back(new Block({ 0,0,tileSize,tileSize }, ToolType::All, 0, RED));
	objects.push_back(new Block({ 0,0,tileSize,tileSize }, ToolType::All, 0, GREEN));
	objects.push_back(new Block({ 0,0,tileSize,tileSize }, ToolType::All, 0, BLUE));
	objects.push_back(new Block({ 0,0,tileSize,tileSize }, ToolType::All, 0, YELLOW));
	objects.push_back(new Block({ 0,0,tileSize,tileSize }, ToolType::All, 0, PINK));
	objects.push_back(new Block({ 0,0,tileSize,tileSize }, ToolType::All, 0, GRAY));
	objects.push_back(new Block({ 0,0,tileSize,tileSize }, ToolType::All, 0, LIGHTGRAY));
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
}

Block* BlockFactory::getObject(int i)
{
	if (i > -1 && i < objects.size())
		return objects[i]->clone();
	return NULL;
}