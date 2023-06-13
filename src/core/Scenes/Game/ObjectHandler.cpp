#include "ObjectHandler.h"
#include "../../../GameObjects/BlockFactory.h"
#include "PerlinNoice.h"
ObjectHandler::ObjectHandler(Rectangle pos)
{
	this->pos = pos;
	tree = new FourTree(pos);
	w = pos.width / tileSize;
	h = pos.height / tileSize;
	blocks = new Block** [(int)(h)];

	PerlinNoice* perlin = new PerlinNoice(w, h);
	perlin->generateNoise2D(6, 1.69, 69);
	float** noice = perlin->getNoice();
	BlockFactory* factory = Blocks;

	for (int i = 0; i < h; i++)
	{
		blocks[i] = new Block * [(int)w];
		for (int j = 0; j < w; j++)
		{

			blocks[i][j] = factory->getObject(factory->getSize()* noice[i][j]);
			if (blocks[i][j] != NULL)
				blocks[i][j]->setMovePos({ (float)j * tileSize,(float)i * tileSize });
		}
			
	}
	delete perlin;


}

ObjectHandler::~ObjectHandler()
{
	clearLists();
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
			if (blocks[i][j] != NULL)
			{
				delete blocks[i][j];
			}
		delete blocks[i];
	}
	delete blocks;
}
void ObjectHandler::clearLists()
{
	update();
	for (GameObject* obj : objects)
		delete obj;
	objects.clear();
}

std::list<GameObject*> ObjectHandler::getObject()
{ 
	std::list<GameObject*> objs;
	for (GameObject* o : objects)
		objs.push_back(o);
	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++)
			if (blocks[i][j] != NULL)
			{
				objs.push_back(blocks[i][j]);
			}
	return objs;
}

std::list<GameObject*> ObjectHandler::getObject(Rectangle pos) 
{ 
	return tree->getObjectsAt(pos); 
}

void ObjectHandler::deleteObject(GameObject* obj) 
{
	objectsToDelete.push_back(obj); 
}

void ObjectHandler::addObject(GameObject* obj) 
{ 
	if (objects.size() < 1000 - objectsToAdd.size())
		objectsToAdd.push_back(obj);
	else
		delete obj;
}

void ObjectHandler::removeObject(GameObject* obj) 
{ 
	objectsToRemove.push_back(obj); 
}

void ObjectHandler::update()
{
	if (objectsToRemove.size() > 0)
	{
		for (GameObject* obj : objectsToRemove)
		{
			objects.remove(obj);
			tree->removeObj(obj);
		}
		objectsToRemove.clear();
	}
	if (objectsToDelete.size() > 0)
	{
		for (GameObject* obj : objectsToDelete)
		{
			objects.remove(obj);
			tree->removeObj(obj);
			delete obj;
		}
		objectsToDelete.clear();
	}
	if (objectsToAdd.size() > 0)
	{
		for (GameObject* obj : objectsToAdd)
		{
			objects.push_back(obj);
			tree->addObj(obj);
		}

		objectsToAdd.clear();
	}

	
}

bool ObjectHandler::addBlock(Block* block,int x,int y)
{
	if (blocks[y][x] == NULL)
	{
		blocks[y][x] = block;
		return true;
	}
	return false;
}

void ObjectHandler::deleteBlock(int x, int y)
{
	if (blocks[y][x] != NULL)
	{
		Block* block = blocks[y][x];
		Rectangle pos = block->getPos();
		int w = pos.width / tileSize;
		int h = pos.height / tileSize;
		for (int i = 0; i < w; i++)
			for (int j = 0; j < h; j++)
				blocks[y + j][x + i] = NULL;

		delete block;
		block = NULL;

	}
}

void ObjectHandler::removeBlock(int x, int y)
{
	if (blocks[y][x] != NULL)
	{
		blocks[y][x] = NULL;
	}
}

void ObjectHandler::deleteBlocks(int x, int y, int w, int h)
{
	for (int i = 0; i < w; i++)
		for (int j = 0; j < h; j++)
		{
			deleteBlock(x + i, y + j);
		}
}

std::list<Block*> ObjectHandler::getBlocks(int x, int y, int w, int h)
{
	std::list<Block*> blockToReturn;
	for (int i = 0; i < w; i++)
		for (int j = 0; j < h; j++)
		{
			Block* thisBlock = blocks[y + j][x + i];
			if (thisBlock != NULL)
			{
				bool breaked = false;
				for (Block* b : blockToReturn)
					if (b == thisBlock)
					{
						breaked = true;
						break;
					}
				if(!breaked)
					blockToReturn.push_back(thisBlock);
			}
				
		}
	return blockToReturn;
}

Block* ObjectHandler::getBlock(int x, int y)
{
	return blocks[y][x];
}