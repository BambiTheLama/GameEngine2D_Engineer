#include "ObjectHandler.h"
#include "../../../GameObjects/BlockFactory.h"
#include "PerlinNoice.h"
#include "../../../GameObjects/PlantsFactory.h"
#include <fstream>

ObjectHandler::ObjectHandler(int chunkX,int chunkY, nlohmann::json j)
{
	this->x = chunkX * tileSize * (w - 1);
	this->y = chunkY * tileSize * (h - 1);
	this->chunkX = chunkX;
	this->chunkY = chunkY;
}

ObjectHandler::ObjectHandler(int chunkX, int chunkY)
{
	this->x = chunkX * tileSize * (w - 1);
	this->y = chunkY * tileSize * (h - 1);
	this->chunkX = chunkX;
	this->chunkY = chunkY;
	tree = new FourTree({ (float)x,(float)y,(w - 1) * tileSize,(h - 1) * tileSize });

	PerlinNoice* perlin = new PerlinNoice(w, h);
	perlin->generateNoise2D(10, 1.69, 169*(69*x+2137*y));
	float** noice = perlin->getNoice();
	BlockFactory* factory = Blocks;

	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{

			int blockID = noice[i][j] >= 0 ? 1 : 0;
			Vector2 pos = { x + (float)j * tileSize,y + (float)i * tileSize };
			if (blockID > 0)
			{
				blockID = noice[i][j] * factory->getSize()+1;
				if ((int)(noice[i][j] * 10000) % 100 < 1)
				{
					Plant* plant = Plants->getObject(0);
					plant->setMovePos(pos);
					objectsToAdd.push_back(plant);
				}
				if (blockID == 2)
				{
					int val = (int)(noice[i][j] * 10000) % 100;
					if (val < 6 && val < 69)
					{
						Plant* plant = Plants->getObject(1);
						plant->setMovePos(pos);
						objectsToAdd.push_back(plant);
					}
				}
					

			}

			blocks[i][j] = factory->getObject(blockID);

			if (blocks[i][j])
				blocks[i][j]->setMovePos(pos);
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
			if (blocks[i][j])
			{
				delete blocks[i][j];
			}
	}
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
	reloadBlock();
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
		int startX = (pos.x - x) / tileSize - 1;
		int startY = (pos.y - y) / tileSize - 1;
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
void ObjectHandler::updatePos(GameObject* obj) 
{ 
	if (isObjAtThisChunk(obj))
	{
		if (tree->hasObj(obj))
		{
			tree->updatePos(obj);
		}
		else
		{
			tree->addObj(obj);
			for (auto o : objects)
				if (o == obj)
				{
					return;
				}
			objects.push_back(obj);
		}
		
	}
	else
	{
		if (tree->hasObj(obj))
		{
			tree->removeObj(obj);
			objects.remove(obj);
		}
			
	}

	
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



	int startX = (pos.x - this->x) / tileSize - 1;
	int startY = (pos.y - this->y) / tileSize - 1;
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

void ObjectHandler::addObject(GameObject* obj) 
{ 
	if (CheckCollisionRecs(obj->getPos(), { (float)x,(float)y,tileSize * w,tileSize * h }))
	{
		objectsToAdd.push_back(obj);
	}
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



bool ObjectHandler::addBlock(Block* block)
{
	Rectangle pos=block->getPos();
	int x = pos.x - this->x;
	if (x >= w * tileSize)
		return false;
	int y = pos.y - this->y;
	if (y >= h * tileSize)
		return false;
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
	int sx = x - this->x;
	int sy = y - this->y;
	int ex = w / tileSize;
	int ey = h / tileSize;
	std::list<Block*> blockToReturn;
	for (int i = 0; i < ex; i++)
		for (int j = 0; j < ey; j++)
		{
			Block* thisBlock = blocks[sy + j][sx + i];
			if (thisBlock)
			{
				blockToReturn.push_back(thisBlock);
			}
				
		}
	return blockToReturn;
}

Block* ObjectHandler::getBlock(int x, int y)
{
	int ix = 0;
	int iy = 0;
	if (x >= this->x && x < this->x + w * tileSize)
		ix = (x - this->x) / tileSize;
	else
		return NULL;
	if (y >= this->y && y < this->y + h * tileSize)
		iy = (y - this->y) / tileSize;
	else
		return NULL;
	return blocks[iy][ix];
}

void ObjectHandler::reloadBlock()
{
	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++)
			if (blocks[i][j])
				blocks[i][j]->start();
}

void ObjectHandler::saveGame(nlohmann::json &j)
{

	std::string name = "CHUNK " + std::to_string(chunkX) + " " + std::to_string(chunkY);
	for (int x = 0; x < w; x++)
		for (int y = 0; y < h; y++)
			if (blocks[y][x])
				j[name]["BLockArray"][y][x] = blocks[y][x]->getID();
}

bool ObjectHandler::isObjAtThisChunk(GameObject *obj)
{
	return CheckCollisionRecs(obj->getPos(), { (float)x,(float)y,tileSize * (w - 1),tileSize * (h - 1) });
}

bool ObjectHandler::isObjAtThisChunk(Rectangle pos)
{
	return CheckCollisionRecs(pos, { (float)x,(float)y,tileSize * (w - 1),tileSize * (h - 1) });
}
