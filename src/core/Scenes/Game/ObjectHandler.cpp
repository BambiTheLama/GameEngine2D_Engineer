#include "ObjectHandler.h"
#include "../../../GameObjects/BlockFactory.h"
#include "PerlinNoice.h"
#include "../../../GameObjects/PlantsFactory.h"
ObjectHandler::ObjectHandler(Rectangle pos)
{
	this->pos = pos;
	tree = new FourTree(pos);
	w = pos.width / tileSize;
	h = pos.height / tileSize;
	blocks = new Block** [(int)(h)];

	PerlinNoice* perlin = new PerlinNoice(w, h);
	perlin->generateNoise2D(10, 1.69, 369);
	float** noice = perlin->getNoice();
	BlockFactory* factory = Blocks;

	for (int i = 0; i < h; i++)
	{
		blocks[i] = new Block * [(int)w];
		for (int j = 0; j < w; j++)
		{
			//printf("%c", (char)(factory->getSize() *noice[i][j]+'a'));

			int blockID = noice[i][j] >= 0 ? 1 : 0;
			if (blockID > 0)
			{
				blockID = noice[i][j] * factory->getSize()+1;
				if ((int)(noice[i][j] * 10000) % 100 < 1)
				{
					Plant* plant = Plants->getObject(0);
					plant->setMovePos({ (float)j * tileSize,(float)i * tileSize });
					objectsToAdd.push_back(plant);
				}
				if (blockID == 2)
				{
					int val = (int)(noice[i][j] * 10000) % 100;
					if (val < 6 && val < 69)
					{
						Plant* plant = Plants->getObject(1);
						plant->setMovePos({ (float)j * tileSize,(float)i * tileSize });
						objectsToAdd.push_back(plant);
					}
				}
					

			}

			blocks[i][j] = factory->getObject(blockID);
			if (blocks[i][j])
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
			if (blocks[i][j])
			{
				delete blocks[i][j];
			}
		delete blocks[i];
	}
	delete blocks;
}
void ObjectHandler::clearLists()
{
	update(0);
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
			if(blocks[i][j])
				blocks[i][j]->start();
}
std::list<GameObject*> ObjectHandler::getObjects()
{ 
	std::list<GameObject*> objs;
	for (GameObject* o : objects)
		objs.push_back(o);
	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++)
			if (blocks[i][j])
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
				if (blocks[y][x])
					objs.push_back(blocks[y][x]);
	}
	
	return objs;
}

std::list<GameObject*> ObjectHandler::getObjectsToDraw(Rectangle pos)
{
	std::list<GameObject*> objs = tree->getObjectsAt(pos);
	std::list<GameObject*> particles;
	for (auto o : objs)
	{
		if (o->getType() == ObjectType::Particle)
		{
			particles.push_back(o);
		}
	}
	for (auto o : particles)
		objs.remove(o);

	GameObject** tmpObj = new GameObject * [objs.size()];

	int n = 0;

	while (objs.size() > 0)
	{
		int min = INT_MAX;
		GameObject* minObj = NULL;
		for (auto o : objs)
		{
			Rectangle pos = o->getPos();
			if (min>pos.y+pos.height)
			{
				min = pos.y + pos.height;
				minObj = o;
			}
		}
		tmpObj[n] = minObj;
		n++;
		objs.remove(minObj);

	}
	for (int i = 0; i < n; i++)
	{
		objs.push_back(tmpObj[i]);
	}
	for (auto o : particles)
		objs.push_back(o);
	delete tmpObj;



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
	{
		for (int x = startX; x < w; x++)
			if (blocks[y][x])
				objs.push_front(blocks[y][x]);
		
	}


	return objs;
}

void ObjectHandler::deleteObject(GameObject* obj) 
{
	for (auto* o : objectsToDelete)
		if (o == obj)
			return;
	objectsToDelete.push_back(obj); 
}

void ObjectHandler::addObject(GameObject* obj) 
{ 
	if (objects.size() < 69000 - objectsToAdd.size())
	{
		objectsToAdd.push_back(obj);
	}
	else
		delete obj;
}

void ObjectHandler::removeObject(GameObject* obj) 
{ 
	objectsToRemove.push_back(obj); 
}

void ObjectHandler::update(float deltaTime)
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
			obj->start();
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
	if (blocks[y][x])
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
	if (blocks[y][x])
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
			if (thisBlock)
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