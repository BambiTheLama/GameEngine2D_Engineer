#include "GameScene.h"
#include "raylib.h"
#include "../../GameObjects/Player/Player.h"
#include "../../GameObjects/NPCs/Enemy.h"
#include "../Engine.h"
#include "Menu.h"
#include <fstream>
GameScene* GameScene::game = NULL;

GameScene::GameScene()
{
	SetExitKey(0);
	for(int i=-3;i<4;i++)
		for(int j=-3;j<4;j++)
			handler.push_back(new ObjectHandler(i, j));

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
}

GameScene::GameScene(nlohmann::json j)
{
	SetExitKey(0);
	//handler = new ObjectHandler(j);
	GameObject* p = new Player();
	addObject(p);
	cameraTarget = p;
	game = this;
	Rectangle pos = cameraTarget->getPos();
	camera.target = { pos.x + 20.0f, pos.y + 20.0f };
	camera.offset = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };
	camera.rotation = 0.0f;
	camera.zoom = 1.0f;
	start();
}

GameScene::~GameScene()
{
	nlohmann::json j;
	std::ofstream writer;
	for(auto h:handler)
		h->saveGame(j);
	writer.open("World.json");
	writer << j;
	writer.close();
	game = NULL;
	for (auto h : handler)
		delete h;
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


}

void GameScene::addObject(GameObject* obj)
{
	allObj.push_back(obj);
	for (auto h : handler)
		if(h->isObjAtThisChunk(obj))
			h->addObject(obj);
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