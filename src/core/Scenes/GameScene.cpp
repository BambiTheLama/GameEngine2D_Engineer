#include "GameScene.h"
#include "raylib.h"
#include "../../GameObjects/Player/Player.h"
#include "../../GameObjects/NPCs/Enemy.h"
#include "../Engine.h"
#include "Menu.h"
#include <iostream>
#include <fstream>
#include <direct.h>
#include <iostream>
#include <filesystem>
GameScene* GameScene::game = NULL;

GameScene::GameScene(std::string worldName)
{
	struct stat sb;

	const char* savePath = "Saves";
	std::string worldFile = savePath + (std::string)"/" + worldName;
	chunksFile = savePath + (std::string)"/" + worldName + (std::string)"/chunks";
	if (stat(savePath, &sb) != 0)
		_mkdir(savePath);
	if (stat(worldFile.c_str(), &sb) != 0)
		_mkdir(worldFile.c_str());
	if (stat(chunksFile.c_str(), &sb) != 0)
		_mkdir(chunksFile.c_str());



	SetExitKey(0);

	//handler.push_back(new ObjectHandler(0, 0));

	GameObject *p = new Player();

	cameraTarget = p;
	game = this;
	Rectangle pos = cameraTarget->getPos();
	camera.target = { pos.x + 20.0f, pos.y + 20.0f };
	camera.offset = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };
	camera.rotation = 0.0f;
	camera.zoom = 1.0f; 


	this->worldName = worldName;

	if (cameraTarget)
	{
		loadChunksCloseToTarget();
		deleteChunksNotCloseToTarget();
		updatePos(cameraTarget);
	}
	
	for (auto h : handlersToAdd)
	{
		handler.push_back(h);

	}
	handlersToAdd.clear();
	start();
	addObject(p);
}



GameScene::~GameScene()
{
	game = NULL;
	if (mapLoader.joinable())
		mapLoader.join();
	for (auto h : handler)
	{
		saveChunk(h);
		h->clearLists();
		delete h;
	}
	handler.clear();
	userUI.clear();
	for (auto o : allObj)
		delete o;
	for (auto o : toDelete)
		delete o;

	game = NULL;


}
void GameScene::start()
{
	for (auto h : handler)
		h->start();
	addObject(new Enemy());
}
void GameScene::update(float deltaTime)
{
	if (IsKeyReleased(KEY_ESCAPE))
	{
		Engine::setScene(new Menu());
		return;
	}
	Rectangle pos = cameraTarget->getPos();
	camera.target = { pos.x + pos.width/2, pos.y + pos.height/2 };
	if (IsKeyDown(KEY_UP))
		zoom += 0.01;
	if (IsKeyDown(KEY_DOWN))
		zoom -= 0.01;
	camera.zoom = zoom;
	float cameraW = (float)GetScreenWidth()/(zoom);
	float cameraH = (float)GetScreenHeight()/(zoom);
	cameraPos = { camera.target.x - cameraW / 2 - 200,camera.target.y - cameraH / 2 - 100,cameraW + 400,cameraH + 200 };
	int chunkX = cameraTarget->getChunkX();
	int chunkY = cameraTarget->getChunkY();
	Rectangle updatePos = { camera.target.x ,camera.target.y ,(renderDystance * 2 + 2) * ObjectHandler::w * tileSize,(renderDystance * 2 + 2) * ObjectHandler::h * tileSize };
	updatePos.x -= updatePos.width / 2;
	updatePos.y -= updatePos.height / 2;

	cursorPos = GetScreenToWorld2D(GetMousePosition(), camera);
	std::list<GameObject*> objects = getObjects(updatePos,ObjectToGet::getNoBlocks);
	for (GameObject* obj : objects)
		obj->update(deltaTime);
	for(auto h:handler)
		h->update(deltaTime);

	for (auto o : toDelete)
	{
		o->onDestory();
		delete o;
	}

	toDelete.clear();
	for (auto h : handlersToDelete)
	{
		handler.remove(h);
		delete h;
	}
	handlersToDelete.clear();

	if (handlersToAdd.size() > 0)
	{
		for (auto h : handlersToAdd)
		{
			handler.push_back(h);
			for (auto h2 : handler)
			{
				if (((h2->getChunkX() - 1 == h->getChunkX() || h2->getChunkX() + 1 == h->getChunkX()) && h2->getChunkY() == h->getChunkY())
					|| ((h2->getChunkY() - 1 == h->getChunkY() || h2->getChunkY() + 1 == h->getChunkY()) && h2->getChunkX() == h->getChunkX()))
					h2->reloadBlock();
			}
			h->start();
		}

		handlersToAdd.clear();

	}

	


	if (!loadingMap)
	{
		if (this->chunkX != chunkX || this->chunkY != chunkY)
		{
			this->chunkX = chunkX;
			this->chunkY = chunkY;
			deleteChunksNotCloseToTarget();
			if (mapLoader.joinable())
				mapLoader.join();
			mapLoader = std::thread(&GameScene::mapLoaderFun, this);
		}
	}


}

void GameScene::addObject(GameObject* obj)
{

	for (auto h : handler)
		if(h->isObjAtThisChunk(obj))
			h->addObject(obj);
	for (auto o : allObj)
		if (o == obj)
			return;
	allObj.push_back(obj);
}

void GameScene::deleteObject(GameObject* obj)
{
	for (auto h : handler)
		h->removeObject(obj);
	for (auto o : toDelete)
		if (o == obj)
			return;
	allObj.remove(obj);
	toDelete.remove(obj);
	toDelete.push_back(obj);
}

void GameScene::removeObject(GameObject* obj)
{
	for (auto h : handler)
		h->removeObject(obj);
}
std::list<GameObject*> GameScene::getObjects(Rectangle pos, ObjectToGet type)
{
	std::list<GameObject*> objs;
	for (auto h : handler)
		if (h->isObjAtThisChunk(pos))
		{
			std::list<GameObject*> obj = h->getObjects(pos, type);
			if (objs.size() <= 0)
			{
				objs = obj;
				continue;
			}
			for (auto o1 : obj)
			{
				bool breaked = false;
				for (auto o2 : objs)
					if (o1 == o2)
					{
						breaked = true;
						break;
					}
				if (!breaked)
					objs.push_back(o1);
			}

		}

	return objs;
}

void GameScene::updatePos(GameObject* obj)
{
	for (auto h : handler)
		h->updatePos(obj);
}

void GameScene::draw()
{
	std::list<GameObject*> objects = getObjToDraw();
	BeginMode2D(camera);
	for (GameObject* obj : objects)
		obj->draw();
	if (collidersToDraw)
		for(auto h:handler)
			h->draw();
	EndMode2D();
	DrawText(TextFormat("%.2lf", camera.zoom), 0, 50, 20, BLACK);
	for (UserUI* i : userUI)
		i->drawInterface();
	DrawFPS(0, 0);
}

void GameScene::removeBlock(Rectangle pos)
{
	for (auto h : handler)
		if (h->isObjAtThisChunk(pos))
			h->removeBlock(pos.x, pos.y);
}

void GameScene::deleteBlock(Rectangle pos)
{
	for (auto h : handler)
		if(h->isObjAtThisChunk(pos))
			h->deleteBlock(pos.x, pos.y);
}

bool GameScene::addBlock(Block* block)
{
	for (auto h : handler)
		if (h->isObjAtThisChunk(block))
			return h->addBlock(block);
	return false;
}

Block* GameScene::getBlock(Rectangle pos)
{
	for (auto h : handler)
		if (h->isObjAtThisChunk(pos))
			return h->getBlock(pos.x, pos.y);
	return NULL;
}

std::list<Block*> GameScene::getBlocks(Rectangle pos)
{
	std::list<Block*> blocks;
	for (auto h : handler)
		if (h->isObjAtThisChunk(cameraPos))
		{
			if (blocks.size() <= 0)
				blocks = h->getBlocks(pos.x, pos.y, pos.width, pos.height);
			else
			{
				std::list<Block*> bl= h->getBlocks(pos.x, pos.y, pos.width, pos.height);
				for (auto b : bl)
					blocks.push_back(b);

			}
		}
	return blocks;

}

void GameScene::deleteChunksNotCloseToTarget()
{
	if (!cameraTarget)
		return;
	int x = chunkX;
	int y = chunkY;
	int minX = x - renderDystance;
	int maxX = x + renderDystance;
	int minY = y - renderDystance;
	int maxY = y + renderDystance;
	std::list<ObjectHandler*>handlersToDelete;
	for (auto h : handler)
	{
		if (h->getChunkX() < minX || h->getChunkX() > maxX || h->getChunkY() < minY || h->getChunkY() > maxY)
		{
			handlersToDelete.push_back(h);
		}
	}
	for (auto h : handlersToDelete)
	{
		saveChunk(h);
		this->handlersToDelete.remove(h);
		this->handlersToDelete.push_back(h);
	}
}

void GameScene::loadChunksCloseToTarget()
{
	if (!cameraTarget)
		return;
	int x = chunkX;
	int y = chunkY;
	int minX = x - renderDystance;
	int maxX = x + renderDystance;
	int minY = y - renderDystance;
	int maxY = y + renderDystance;

	for (int x = minX; x <= maxX; x++)
		for (int y = minY; y <= maxY; y++)
		{
			loadChunk(x, y);
		}
}


std::list<GameObject*> GameScene::getObjToDraw()
{
	std::list<GameObject*> objects;
	for (auto h : handler)
		if (h->isObjAtThisChunk(cameraPos))
		{
			if (objects.size() <= 0)
			{
				objects = h->getObjectsToDraw(cameraPos);
				continue;
			}
			std::list<GameObject*> objs=h->getObjectsToDraw(cameraPos);

			for (auto o : objs)
				objects.push_back(o);


		}

	return objects;
}

void GameScene::printfChunk(GameObject* obj)
{
	for(auto h:handler)
		if (h->isObjAtThisChunk(obj))
		{
			printf("Chunk %d %d\n", h->getChunkY(), h->getChunkX());
		}
}

void GameScene::generateChunk(int x, int y)
{

	std::string name = "/" + chunkName(x, y);
	nlohmann::json j;
	std::ifstream reader;
	reader.open(chunksFile + name);
	if (reader.is_open())
		reader >> j;
	reader.close();
	ObjectHandler* h = NULL;
	if (j.contains("CHUNK " + std::to_string(x) + " " + std::to_string(y)))
	{
		h = new ObjectHandler(x, y, j);
	}
	else
	{
		h = new ObjectHandler(x, y, 666);
	}
	if (h)
	{
		handlersToAdd.push_back(h);
	}

}
void GameScene::loadChunk(int x, int y)
{
	for (auto hand : handler)
		if (hand->getChunkX() == x && hand->getChunkY() == y)
			return;
	std::string name = "/" + chunkName(x, y);
	nlohmann::json j;
	std::ifstream reader;
	reader.open(chunksFile + name);
	if (reader.is_open())
		reader >> j;
	reader.close();
	ObjectHandler* h = NULL;
	if (j.contains("CHUNK " + std::to_string(x) + " " + std::to_string(y)))
	{
		h = new ObjectHandler(x, y, j);
	}
	else
	{
		generateChunk(x, y);
	}
	if (h)
	{
		handlersToAdd.push_back(h);
	}


}
void GameScene::deleteChunk(ObjectHandler* h)
{
	for (auto h2 : handler)
		if (h == h2)
		{
			saveChunk(h);
			break;
		}
	handler.remove(h);

	handlersToDelete.remove(h);
	handlersToDelete.push_back(h);
}
void GameScene::saveChunk(ObjectHandler* h)
{
	std::string name = "/" + chunkName(h->getChunkX(), h->getChunkY());

	nlohmann::json j;
	std::ifstream reader;
	reader.open(chunksFile + name);
	if (reader.is_open())
	{
		reader >> j;
	}
	reader.close();
	h->update(0.0f);
	h->saveGame(j);
	std::ofstream writer;
	writer.open(chunksFile + name);
	writer << j;
	writer.close();
}

std::string GameScene::chunkName(int x, int y)
{
	std::string name = "c ";
	if (y >= 0)
		name += std::to_string((int)(y / chunkYPerFile)) + " ";
	else
		name += std::to_string((int)((y - chunkYPerFile) / chunkYPerFile)) + " ";
	if (x >= 0)
		name += std::to_string((int)(x / chunkXPerFile));
	else
		name += std::to_string((int)((x - chunkXPerFile) / chunkXPerFile));
	name += ".json";
	return name;
}

void GameScene::mapLoaderFun()
{
	loadingMap = true;
	loadChunksCloseToTarget();
	//deleteChunksNotCloseToTarget();
	loadingMap = false;
}