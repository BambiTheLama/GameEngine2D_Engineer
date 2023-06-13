#include "GameScene.h"
#include "raylib.h"
#include "../../GameObjects/Player/Player.h"


GameScene* GameScene::game = NULL;

GameScene::GameScene()
{
	heandler = new ObjectHandler({0,0,(float)GetScreenWidth(),(float)GetScreenHeight()});
	heandler->addObject(new Player());
	game = this;
}

GameScene::~GameScene()
{
	delete heandler;
;	game = NULL;
}

void GameScene::update()
{
	cursorPos = GetMousePosition();
	std::list<GameObject*> objects = heandler->getObject();
	for (GameObject* obj : objects)
		obj->update();
	heandler->update();

	//printf("Iloœæ elementów: %d\n", objects.size());


}

void GameScene::addObject(GameObject* obj)
{
	heandler->addObject(obj);
}

void GameScene::deleteObject(GameObject* obj)
{
	heandler->deleteObject(obj);
}

void GameScene::removeObject(GameObject* obj)
{
	heandler->removeObject(obj);
}

void GameScene::draw()
{
	std::list<GameObject*> objects = heandler->getObject();
	int n = objects.size(), j = 0;
	GameObject** toDraw = new GameObject * [n];
	
	for (GameObject* obj : objects)
	{
		//obj->draw();
		toDraw[j] = obj;
		for (int i = j; i > 0; i--)
		{
			Rectangle pos1 = toDraw[i]->getPos();
			Rectangle pos2 = toDraw[i - 1]->getPos();
			if (pos1.y + pos1.height < pos2.y + pos2.height)
			{
				toDraw[i] = toDraw[i - 1];
				toDraw[i - 1] = obj;
			}
		}

		j++;
	}
	for (int i = 0; i < n; i++)
		toDraw[i]->draw();
	delete toDraw;
	heandler->draw();
}

void GameScene::removeBlocks(Rectangle pos)
{
	int xIndex = pos.x / tileSize;
	int yIndex = pos.y / tileSize;
	int wMove = pos.width / tileSize;
	int hMove = pos.height / tileSize;
	for (int i = 0; i < wMove; i++)
		for (int j = 0; j < hMove; j++)
			heandler->removeBlock(xIndex + i, yIndex + j);
}

void GameScene::deleteBlocks(Rectangle pos)
{
	int xIndex = pos.x / tileSize;
	int yIndex = pos.y / tileSize;
	int wMove = pos.width / tileSize;
	int hMove = pos.height / tileSize;
	heandler->deleteBlocks(xIndex, yIndex, wMove, hMove);
}

bool GameScene::addBlock(Block* block)
{
	Rectangle pos = block->getPos();
	int xIndex = pos.x / tileSize;
	int yIndex = pos.y / tileSize;
	int wMove = pos.width / tileSize;
	int hMove = pos.height / tileSize;
	
	std::list<Block*> blocks = heandler->getBlocks(xIndex, yIndex, wMove, hMove);
	if (blocks.size() > 0)
		return false;
	for (int x = 0; x < wMove; x++)
		for (int y = 0; y < hMove; y++)
		{
			heandler->addBlock(block, x + xIndex, y + yIndex);
		}
	return true;
}

Block* GameScene::getBlock(Rectangle pos)
{
	int xIndex = pos.x / tileSize;
	int yIndex = pos.y / tileSize;
	return heandler->getBlock(xIndex, yIndex);
}

std::list<Block*> GameScene::getBlocks(Rectangle pos)
{
	int xIndex = pos.x / tileSize;
	int yIndex = pos.y / tileSize;
	int wMove = pos.width / tileSize;
	int hMove = pos.height / tileSize;
	return heandler->getBlocks(xIndex, yIndex, wMove, hMove);
}