#include "GameScene.h"
#include "raylib.h"
#include "../../GameObjects/Player/Player.h"


GameScene* GameScene::game = NULL;

GameScene::GameScene()
{
	heandler = new ObjectHandler({0,0,64000.0f,64000.0f});
	heandler->addObject(cameraTarget=new Player());
	game = this;
	Rectangle pos = cameraTarget->getPos();
	camera.target = { pos.x + 20.0f, pos.y + 20.0f };
	camera.offset = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };
	camera.rotation = 0.0f;
	camera.zoom = 1.0f;
}

GameScene::~GameScene()
{
	delete heandler;
;	game = NULL;
}

void GameScene::update()
{
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
	//printf("CAMERAPOS ={%lf %lf %lf %lf}\n",cameraPos.x, cameraPos.y, cameraPos.width, cameraPos.height);
	Rectangle updatePos = { camera.target.x - cameraW ,camera.target.y - cameraH ,cameraW*2,cameraH*2 };
	cursorPos = GetScreenToWorld2D(GetMousePosition(), camera);
	std::list<GameObject*> objects = heandler->getObjects(updatePos);
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

	std::list<GameObject*> objects = heandler->getObjectsToDraw(cameraPos);


	BeginMode2D(camera);
	for (GameObject* obj : objects)
		obj->draw();
	heandler->draw();
	EndMode2D();
	DrawText(TextFormat("%.2lf", camera.zoom), 0, 50, 20, BLACK);
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
	if (xIndex < 0)
		xIndex = 0;
	int yIndex = pos.y / tileSize;
	if (yIndex < 0)
		yIndex = 0;
	int wMove = pos.width / tileSize;
	if (wMove <= 0)
		wMove = 1;
	int hMove = pos.height / tileSize;
	if (hMove <= 0)
		hMove = 1;
	return heandler->getBlocks(xIndex, yIndex, wMove, hMove);
}