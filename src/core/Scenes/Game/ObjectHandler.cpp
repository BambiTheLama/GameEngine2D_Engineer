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
			//printf("%c", (char)(factory->getSize() *noice[i][j]+'a'));
			blocks[i][j] = factory->getObject(noice[i][j] >= 0 ? 1 : 0);
			if (blocks[i][j] != NULL)
				blocks[i][j]->setMovePos({ (float)j * tileSize,(float)i * tileSize });
		}
		//printf("\n");
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
void ObjectHandler::start()
{
	for (GameObject* obj : objects)
		obj->start();
	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++)
			if(blocks[i][j]!=NULL)
				blocks[i][j]->start();
}
std::list<GameObject*> ObjectHandler::getObjects()
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

std::list<GameObject*> ObjectHandler::getObjects(Rectangle pos, ObjectToGet type)
{
	std::list<GameObject*> objs;
	if (type != ObjectToGet::getBlocks)
	{
		objs = tree->getObjectsAt(pos);
	}
	if (type != ObjectToGet::getNoBlocks)
	{
		int startX = pos.x / tileSize - 1;
		int startY = pos.y / tileSize - 1;
		if (startX < 0)
			startX = 0;
		if (startY < 0)
			startY = 0;
		int w = pos.width / tileSize + startX + 3;
		int h = pos.height / tileSize + startY + 3;
		if (w >= this->w)
			w = this->w - 1;
		if (h >= this->h)
			h = this->h - 1;
		for (int y = startY; y < h; y++)
			for (int x = startX; x < w; x++)
				if (blocks[y][x] != NULL)
					objs.push_back(blocks[y][x]);
	}
	
	return objs;
}

std::list<GameObject*> ObjectHandler::getObjectsToDraw(Rectangle pos)
{
	std::list<GameObject*> objs = tree->getObjectsAt(pos);
	int n = objs.size();
	GameObject** objs2 = new GameObject * [n];
	int i = 0;
	while (objs.size() > 0)
	{
		GameObject* min=NULL;
		for (GameObject* o : objs)
		{
			if (min == NULL)
			{
				min = o;
				continue;
			}
			Rectangle pos1 = min->getPos();
			Rectangle pos2 = o->getPos();
			if (pos1.y > pos2.y)
			{
				min = o;
			}
		}
		objs.remove(min);
		objs2[i] = min;
		i++;
	}

	int startX = pos.x / tileSize - 1;
	int startY = pos.y / tileSize - 1;
	if (startX < 0)
		startX = 0;
	if (startY < 0)
		startY = 0;
	int w = pos.width / tileSize + startX + 3;
	int h = pos.height / tileSize + startY + 3;
	if (w >= this->w)
		w = this->w - 1;
	if (h >= this->h)
		h = this->h - 1;
	i = 0;
	for (int y = startY; y < h; y++)
	{
		for (int j = i; j < n; j++)
		{
			Rectangle objPos = objs2[j]->getPos();
			if (objPos.y+objPos.height > (y+1) * tileSize)
			{
				break;
			}
			objs.push_back(objs2[i]);
			i++;
		}
		for (int x = startX; x < w; x++)
			if (blocks[y][x] != NULL)
				objs.push_back(blocks[y][x]);
		
	}
	for (; i < n; i++)
		objs.push_back(objs2[i]);
	delete objs2;
	return objs;
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
		objectsToDelete.push_back(blocks[y][x]);
		Rectangle pos = blocks[y][x]->getPos();
		int w = pos.width / tileSize;
		int h = pos.height / tileSize;
		for (int i = 0; i < w; i++)
			for (int j = 0; j < h; j++)
				blocks[y + j][x + i] = NULL;
		
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
	if (x + w >= this->w)
	{
		w = this->w - x;
	}
	if (y + h >= this->h)
	{
		h = this->h - y;
	}
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