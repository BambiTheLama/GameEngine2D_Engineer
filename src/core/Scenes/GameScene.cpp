#include "GameScene.h"
#include "raylib.h"
#include "../../GameObjects/Player/Player.h"
#include "../../GameObjects/NPCs/Enemy.h"
#include "../Engine.h"
#include "Menu.h"
#include <iostream>
#include <fstream>
GameScene* GameScene::game = NULL;

GameScene::GameScene(std::string worldName)
{
	SetExitKey(0);

	//handler.push_back(new ObjectHandler(0, 0));

	GameObject *p = new Player();
	addObject(p);
	cameraTarget = p;
	game = this;
	Rectangle pos = cameraTarget->getPos();
	camera.target = { pos.x + 20.0f, pos.y + 20.0f };
	camera.offset = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };
	camera.rotation = 0.0f;
	camera.zoom = 1.0f; 
	start();

	this->worldName = worldName;
	std::ifstream reader;
	reader.open(this->worldName, std::ios::binary);
	if (reader.is_open())
	{
		reader >> j;
	}
	else
	{
		int perlinW = 6400, perlinH = 1800;
		int perlinSize = 16;
		PerlinNoice* water = new PerlinNoice(perlinW, perlinH, perlinSize);
		PerlinNoice* bioms = new PerlinNoice(perlinW, perlinH, perlinSize);
		PerlinNoice* terain = new PerlinNoice(perlinW, perlinH, perlinSize);
		int chunkSizeX = ObjectHandler::h;
		int startX = -(perlinW * perlinSize) / ((ObjectHandler::w - 1) * tileSize * 2);
		if ((perlinW * perlinSize) % ((ObjectHandler::w - 1) * tileSize * 2))
			startX--;
		int startY = -(perlinH * perlinSize) / ((ObjectHandler::h - 1) * tileSize * 2);
		if ((perlinH * perlinSize) % ((ObjectHandler::h - 1) * tileSize * 2))
			startY--;
		int endX = -startX;
		int endY = -startY;
		water->generateNoise2D(7, 2.6, 69);
		bioms->generateNoise2D(2, 1, 2137);
		terain->generateNoise2D(7, 2, 69, 666);
		
		for (int y = startY; y < endY; y++)
		{
			for (int x = startX; x < endX; x++)
			{
				ObjectHandler* handler = new ObjectHandler(x, y, terain, water, bioms);
				handler->saveGame(j);
				delete handler;
			}
			printf("GENERETED FULL ROW %d\n", y);
		}
		delete water;
		delete bioms;
		delete terain;
		std::ofstream writer;
		writer.open(worldName, std::ios::out | std::ios::binary);
		writer << j;
		writer.close();
	}
	reader.close();

	if (cameraTarget)
	{
		loadChunksCloseToTarget();
		deleteChunksNotCloseToTarget();
		updatePos(cameraTarget);
	}
	

}



GameScene::~GameScene()
{
	if (mapLoader.joinable())
		mapLoader.join();
	game = NULL;
	for (auto h : handler)
	{
		h->saveGame(j);
		h->clearLists();
		delete h;
	}
	handler.clear();

	std::ofstream writer;
	writer.open(worldName, std::ios::binary);
	writer << j;
	writer.close();

	for (auto o : allObj)
		delete o;
	for (auto o : toDelete)
		delete o;

	game = NULL;
	userUI.clear();	

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
	cameraPos = { camera.target.x - cameraW / 2,camera.target.y - cameraH / 2,cameraW,cameraH };
	int chunkX = cameraTarget->getChunkX();
	int chunkY = cameraTarget->getChunkY();

	Rectangle updatePos = { camera.target.x - cameraW ,camera.target.y - cameraH ,cameraW*2,cameraH*2 };
	cursorPos = GetScreenToWorld2D(GetMousePosition(), camera);
	std::list<GameObject*> objects = getObjects(updatePos,ObjectToGet::getNoBlocks);
	for (GameObject* obj : objects)
		obj->update(deltaTime);
	for(auto h:handler)
		h->update(deltaTime);

	for (auto o : toDelete)
		delete o;
	toDelete.clear();
	for (auto h : handlersToDelete)
		delete h;
	handlersToDelete.clear();
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

void GameScene::removeBlocks(Rectangle pos)
{
	int w, h;
	w = pos.width / tileSize;
	h = pos.height / tileSize;
	for (int i = 0; i < w; i++)
		for (int j = 0; j < h; j++)
			for (auto h : handler)
				h->removeBlock(pos.x, pos.y);
}

void GameScene::deleteBlocks(Rectangle pos)
{
	int w, h;
	w = pos.width / tileSize;
	h = pos.height / tileSize;
	for (int i = 0; i < w; i++)
		for (int j = 0; j < h; j++)
			for (auto h : handler)
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
	
	for (auto h : handler)
	{
		if (h->getChunkX() < minX || h->getChunkX() > maxX || h->getChunkY() < minY || h->getChunkY() > maxY)
			handlersToDelete.push_back(h);
	}
	for (auto h : handlersToDelete)
	{
		h->saveGame(j);
		handler.remove(h);
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
			bool breaked = false;
			for (auto h : handler)
				if (h->getChunkX() == x && h->getChunkY() == y)
				{
					breaked = true;
					break;
				}
			if (!breaked)
			{
				ObjectHandler* objH = new ObjectHandler(x, y, j);
				handler.push_back(objH);
				objH->start();
			}
		}

	for (auto h : handler)
		h->reloadBlock();


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
void GameScene::mapLoaderFun()
{
	loadingMap = true;
	loadChunksCloseToTarget();
	loadingMap = false;
}