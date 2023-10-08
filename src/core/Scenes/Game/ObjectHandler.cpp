#include "ObjectHandler.h"
#include "../../../GameObjects/BlockFactory.h"
#include "PerlinNoice.h"
#include "../../../GameObjects/PlantsFactory.h"
#include <fstream>
#include "../GameScene.h"

ObjectHandler::ObjectHandler(int chunkX,int chunkY, nlohmann::json j)
{
	this->x = chunkX * tileSize * (w - 1);
	this->y = chunkY * tileSize * (h - 1);
	this->chunkX = chunkX;
	this->chunkY = chunkY;
	BlockFactory* factory = Blocks;
	tree = new FourTree({ (float)x,(float)y,(w - 1) * tileSize,(h - 1) * tileSize });
	nlohmann::json toRead;
	std::string name = "CHUNK " + std::to_string(chunkX) + " " + std::to_string(chunkY);
	if (j.contains(name))
	{
		toRead = j[name];
	}

	if (toRead.contains("BLockArray"))
	{
		nlohmann::json toReadBlock=toRead["BLockArray"];
		int k = 0;
		int ID = toReadBlock[k]["ID"];
		int times = toReadBlock[k]["t"];
		for (int y = 0; y < h; y++)
		{
			for (int x = 0; x < w; x++)
			{
				if (times <= 0)
				{
					k++;
					ID = toReadBlock[k]["ID"];
					times = toReadBlock[k]["t"];
				}

				blocks[y][x] = factory->getObject(ID);
				Vector2 pos = { this->x + x * tileSize,this->y + y * tileSize };
				blocks[y][x]->setMovePos(pos);
				times--;

			}
		}


		if (toRead.contains("OBJS"))
		{
			nlohmann::json toReadObjs = toRead["OBJS"];
			for (int i = 0; i < toReadObjs.size(); i++)
			{
				ObjectType type = (ObjectType)toReadObjs[i]["ObjClass"];
				int ID = toReadObjs[i]["ID"];
				GameObject* obj = getObjFromFactory(type, ID);
				if (obj)
				{
					obj->readFromJson(toReadObjs[i]);
					obj->generateChunk();
					objects.push_back(obj);
				}
			}
		}

		
	}
	else
	{
		for (int x = 0; x < w; x++)
			for (int y = 0; y < h; y++)
			{
				Vector2 pos = { this->x + x * tileSize,this->y + y * tileSize };
				blocks[y][x] = factory->getObject(0);
				blocks[y][x]->setMovePos(pos);

			}
	}
	Rectangle pos = { (float)x,(float)y-1,(w-1) * tileSize,1.0f };
	std::list<GameObject*> obj = Game->getObjects(pos, ObjectToGet::getNoBlocks);
	for (auto o : obj)
		addObject(o);
	pos.y += tileSize * (h - 1)+2;
	obj = Game->getObjects(pos, ObjectToGet::getNoBlocks);
	for (auto o : obj)
		addObject(o);

	pos = { (float)x-1,(float)y,1.0f,(h-1)*tileSize };
	obj = Game->getObjects(pos, ObjectToGet::getNoBlocks);
	for (auto o : obj)
		addObject(o);
	pos.x += tileSize * (w - 1)+2;
	obj = Game->getObjects(pos, ObjectToGet::getNoBlocks);
	for (auto o : obj)
		addObject(o);
}
ObjectHandler::ObjectHandler(int chunkX, int chunkY, PerlinNoice* terain, PerlinNoice* water, PerlinNoice* bioms)
{
	this->x = chunkX * tileSize * (w - 1);
	this->y = chunkY * tileSize * (h - 1);
	this->chunkX = chunkX;
	this->chunkY = chunkY;
	BlockFactory* factory = Blocks;
	tree = new FourTree({ (float)x,(float)y,(w - 1) * tileSize,(h - 1) * tileSize });
	for (int x = 0; x < w; x++)
		for (int y = 0; y < h; y++)
		{
			int id = 0;
			Vector2 pos = { this->x + x * tileSize,this->y + y * tileSize };
			float waterV = water->getValue(pos.x, pos.y);
			float terainV = terain->getValue(pos.x, pos.y);
			float biomsV = bioms->getValue(pos.x, pos.y);
			if (waterV < 0.0213769)
				id = 0;
			else
			{
				if (waterV < 0.069)
					id = 1;
				else
					id = 2;
			}

			blocks[y][x] = factory->getObject(id);
			blocks[y][x]->setMovePos(pos);
			if (id == 2)
			{
				GameObject* o = NULL;
				if ((int)(biomsV * 10000) % 100 == 0)
				{
					o = Plants->getObject(0);
				}
				else if ((int)(biomsV * 10000) % 400 == 2)
				{
					o = Plants->getObject(1);
				}
				if (o != NULL)
				{
					o->setMovePos({ pos });
					objects.push_back(o);
					o->generateChunk();
				}
			}
		}
}
ObjectHandler::ObjectHandler(int chunkX, int chunkY)
{
	this->x = chunkX * tileSize * (w - 1);
	this->y = chunkY * tileSize * (h - 1);
	this->chunkX = chunkX;
	this->chunkY = chunkY;
	tree = new FourTree({ (float)x,(float)y,(w - 1) * tileSize,(h - 1) * tileSize });

	PerlinNoice* perlin = new PerlinNoice(w, h);
	perlin->generateNoise2D(10, 1.69, 692137);
	float** noice = perlin->getNoice();
	BlockFactory* factory = Blocks;

	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{

			int blockID = noice[i][j] >= 0 ? 1 : 1;
			Vector2 pos = { x + (float)j * tileSize,y + (float)i * tileSize };


			blocks[i][j] = factory->getObject(blockID);

			if (blocks[i][j])
				blocks[i][j]->setMovePos(pos);
		}

	}
	delete perlin;
}



ObjectHandler::~ObjectHandler()
{
	GameScene* game = Game;
	if (game)
	{
		for (GameObject* o : objects)
		{
			if (chunkX != o->getChunkX() || chunkY != o->getChunkY())
				continue;

			game->deleteObject(o);
		}
	}
	else
	{
		for (GameObject* o : objects)
		{
			if (chunkX != o->getChunkX() || chunkY != o->getChunkY())
				continue;
			delete o;
		}
	}
	clearLists();
	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
			if (blocks[y][x])
			{
				delete blocks[y][x];
			}
	}
	if(tree)
		delete tree;
}
void ObjectHandler::clearLists()
{
	objectsToDelete.clear();
	objectsToRemove.clear();
	objectsToAdd.clear();
	objects.clear();
}

void ObjectHandler::start()
{
	for (GameObject* obj : objects)
	{
		obj->start();
		Game->addObject(obj);
	}

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
	if (CheckCollisionRecs(obj->getPos(), { (float)x,(float)y,tileSize * (w - 1),tileSize * (h - 1) }))
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
				blocks[i][j]->generateTexturePos();
}

void ObjectHandler::reloadBlockUp()
{
	for (int j = 0; j < w; j++)
		if (blocks[0][j])
			blocks[0][j]->generateTexturePos();
}
void ObjectHandler::reloadBlockDown()
{
	int y = h - 1;
	for (int j = 0; j < w; j++)
		if (blocks[y][j])
			blocks[y][j]->generateTexturePos();
}
void ObjectHandler::reloadBlockLeft()
{
	for (int i = 0; i < h; i++)
		if (blocks[i][0])
			blocks[i][0]->generateTexturePos();
}
void ObjectHandler::reloadBlockRight()
{
	int x = w - 1;
	for (int i = 0; i < h; i++)
		if (blocks[i][x])
			blocks[i][x]->generateTexturePos();
}
void ObjectHandler::saveGame(nlohmann::json &j)
{
	nlohmann::json toSave;
	int ID = 0;
	int times = 0;
	int k = 0;
	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			if (blocks[y][x])
			{
				if (blocks[y][x]->getID() != ID)
				{
					if (times > 0)
					{
						toSave["BLockArray"][k]["ID"] = ID;
						toSave["BLockArray"][k]["t"] = times;
						k++;
					}
					ID = blocks[y][x]->getID();
					times = 1;
				}
				else
				{
					times++;
				}
			}
				
		}

	}
	toSave["BLockArray"][k]["ID"] = ID;
	toSave["BLockArray"][k]["t"] = times;

	int i = 0;
	for (auto o : objects)
	{
		if (o->destoryAfterRenderClear())
			continue;
		if (chunkX != o->getChunkX() || chunkY != o->getChunkY())
			continue;
		o->saveToJson(toSave["OBJS"][i]);
		i++;
	}
	std::string name = "CHUNK " + std::to_string(chunkX) + " " + std::to_string(chunkY);
	j[name] = toSave;
}

bool ObjectHandler::isObjAtThisChunk(GameObject *obj)
{
	return CheckCollisionRecs(obj->getPos(), { (float)x,(float)y,tileSize * (w - 1),tileSize * (h - 1) });
}

bool ObjectHandler::isObjAtThisChunk(Rectangle pos)
{
	return CheckCollisionRecs(pos, { (float)x,(float)y,tileSize * (w - 1),tileSize * (h - 1) });
}
