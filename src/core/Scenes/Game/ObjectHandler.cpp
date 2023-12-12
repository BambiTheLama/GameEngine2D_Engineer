#include "ObjectHandler.h"
#include "../../../GameObjects/BlockFactory.h"
#include "../../../GameObjects/StructuresFactory.h"
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
					if (k < toReadBlock.size())
					{
						ID = toReadBlock[k]["ID"];
						times = toReadBlock[k]["t"];
					}
					else
					{
						ID = 0;
						times = 999;
					}
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
					addObject(obj);
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
ObjectHandler::ObjectHandler(int chunkX, int chunkY, float seed)
{
	FastNoiseLite terrain(seed);
	terrain.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2S);
	terrain.SetFrequency(0.0102f);
	terrain.SetFractalType(FastNoiseLite::FractalType_FBm);
	terrain.SetFractalOctaves(3);
	terrain.SetFractalGain(1.48f);
	terrain.SetFractalLacunarity(10.29f);
	terrain.SetFractalWeightedStrength(0.0f);


	FastNoiseLite water(seed+1);
	water.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
	water.SetFrequency(0.000302f);
	water.SetFractalType(FastNoiseLite::FractalType_FBm);
	water.SetFractalOctaves(6);
	water.SetFractalGain(0.542f);
	water.SetFractalLacunarity(0.463f);
	water.SetFractalWeightedStrength(0.53f);






	FastNoiseLite friendly;
	friendly.SetSeed(seed + 2);
	friendly.SetFrequency(0.0000269f);
	friendly.SetFractalType(FastNoiseLite::FractalType_FBm);
	friendly.SetFractalOctaves(7);
	friendly.SetFractalGain(0.47f);
	friendly.SetFractalLacunarity(1.75f);

	FastNoiseLite temperature(seed + 3);
	temperature.SetNoiseType(FastNoiseLite::NoiseType_ValueCubic);
	temperature.SetFractalType(FastNoiseLite::FractalType_FBm);
	temperature.SetFractalOctaves(3);
	temperature.SetFrequency(0.0005123f);
	temperature.SetFractalLacunarity(0.45f);
	temperature.SetFractalGain(3.18f);
	temperature.SetFractalWeightedStrength(4.490f);


	this->x = chunkX * tileSize * (w - 1);
	this->y = chunkY * tileSize * (h - 1);
	this->chunkX = chunkX;
	this->chunkY = chunkY;
	BlockFactory* factory = Blocks;
	tree = new FourTree({ (float)x,(float)y,(w - 1) * tileSize,(h - 1) * tileSize });
	for (int x = 0; x < w; x++)
		for (int y = 0; y < h; y++)
		{

			Vector2 pos = { this->x + x * tileSize,this->y + y * tileSize };
			float waterV = water.GetNoise(pos.x, pos.y);
			float terainV = terrain.GetNoise(pos.x, pos.y);
			float friendlyV = friendly.GetNoise(pos.x, pos.y);
			float temperatureV = temperature.GetNoise(pos.x, pos.y);
			int nbioms = 4;

			if ((friendlyV < -0.3 && temperatureV > 0.6) || (friendlyV < -0.1 && temperatureV > 0.8))
			{
				generateDesertBiom(factory, pos, waterV, terainV, x, y);
			}
			else if ((friendlyV < -0.3 && temperatureV < -0.4) || (friendlyV < -0.1 && temperatureV < -0.6))
			{
				generateSnowBiom(factory, pos, waterV, terainV, x, y);
			}
			else if ((friendlyV > 0.0 && temperatureV > -0.3f) || friendlyV > 0.8f)
			{
				generateForestBiom(factory, pos, waterV, terainV, x, y);
			}
			else 
			{
				generateStoneBiom(factory, pos, waterV, terainV, x, y);
			}
		}
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
	if (!hasObjectAtList(obj) && CheckCollisionRecs(obj->getPos(), {(float)x,(float)y,tileSize * (w - 1),tileSize * (h - 1)}))
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
	int x = (pos.x - this->x)/ tileSize;
	if (x >= w || x < 0)
		return false;
	int y = (pos.y - this->y) / tileSize;
	if (y >= h || y < 0)
		return false;
	if (!blocks[y][x])
	{
		blocks[y][x] = block;
		for (int i = -1; i < 2; i++)
			for (int j = -1; j < 2; j++)
			{
				if (i + y < 0 || i + y >= h || x + j<0 || x + j>w)
					continue;
				if(blocks[y + i][x + j])
					blocks[y + i][x + j]->generateTexturePos();
			}

		return true;
	}
	return false;
}

void ObjectHandler::deleteBlock(int x, int y)
{
	y -= this->y;
	x -= this->x;
	x /= tileSize;
	y /= tileSize;
	if (y < 0 || x < 0 || x >= w || y >= h)
		return;
	if (blocks[y][x])
	{
		Rectangle pos = blocks[y][x]->getPos();
		int w = pos.width / tileSize;
		int h = pos.height / tileSize;
		for (int i = 0; i < w; i++)
			for (int j = 0; j < h; j++)
			{
				blocks[y + j][x + i] = NULL;
			}

		objectsToDelete.push_back(blocks[y][x]);

		for (int i = -1; i < 2; i++)
			for (int j = -1; j < 2; j++)
			{
				if (i + y < 0 || i + y >= h || x + j<0 || x + j>w)
					continue;
				if (blocks[y + i][x + j])
					blocks[y + i][x + j]->generateTexturePos();
			}
	}
}

void ObjectHandler::removeBlock(int x, int y)
{
	y -= this->y;
	x -= this->x;
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
	for(auto o:objects)
	{
		if (o->getType() != ObjectType::Structure)
			continue;
		Structure* s = dynamic_cast<Structure*>(o);
		
		if (s)
			s->generateTexturePos();
	}
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
		o->generateChunk();
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
bool ObjectHandler::hasObjectAtList(GameObject* obj)
{
	for (auto o : objects)
		if (o == obj)
			return true;
	for (auto o : objectsToAdd)
		if (o == obj)
			return true;
	return false;
}
bool ObjectHandler::isObjAtThisChunk(Rectangle pos)
{
	return CheckCollisionRecs(pos, { (float)x,(float)y,tileSize * (w - 1),tileSize * (h - 1) });
}
void ObjectHandler::generateForestBiom(BlockFactory *factory,Vector2 pos,float waterV,float terrainV, int x, int y)
{

	int id = 0;
	if (waterV < 0)
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
		if ((int)(terrainV * 10000) % 100 == 0)
		{
			o = Structures->getObject(0);
		}
		else if ((int)(terrainV * 10000) % 400 == 2)
		{
			o = Structures->getObject(1);
		}
		if (o)
		{
			o->setMovePos({ pos });
			addObject(o);
			o->generateChunk();
		}
	}
}
void ObjectHandler::generateSnowBiom(BlockFactory* factory, Vector2 pos, float waterV, float terrainV, int x, int y)
{
	int id = 0;
	if (waterV < -0.09)
		id = 0;
	else if (waterV < 0)
		id = 6;
	else
		id = 5;

	blocks[y][x] = factory->getObject(id);
	blocks[y][x]->setMovePos(pos);
}
void ObjectHandler::generateStoneBiom(BlockFactory* factory, Vector2 pos, float waterV, float terrainV, int x, int y)
{
	int id = 0;
	if (waterV < 0)
		id = 0;
	else
		id = 4;

	blocks[y][x] = factory->getObject(id);
	blocks[y][x]->setMovePos(pos);
	if (id == 4)
	{
		GameObject* o = NULL;
		if ((int)(terrainV * 10000) % 100 == 0)
		{
			o = Structures->getObject(2);
		}
		if (o)
		{
			o->setMovePos({ pos });
			addObject(o);
			o->generateChunk();
		}
	}
}
void ObjectHandler::generateDesertBiom(BlockFactory* factory, Vector2 pos, float waterV, float terrainV,int x, int y)
{
	int id = 0;
	if (waterV < 0)
		id = 0;
	else
		id = 1;

	blocks[y][x] = factory->getObject(id);
	blocks[y][x]->setMovePos(pos);
}