#include "GameScene.h"
#include "raylib.h"
#include "../../GameObjects/Player/Player.h"


GameScene* GameScene::game = NULL;

GameScene::GameScene()
{
	handler = new ObjectHandler({0,0,32000.0f,32000.0f});
	handler->addObject(cameraTarget=new Player());
	game = this;
	Rectangle pos = cameraTarget->getPos();
	camera.target = { pos.x + 20.0f, pos.y + 20.0f };
	camera.offset = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };
	camera.rotation = 0.0f;
	camera.zoom = 1.0f;
}

GameScene::~GameScene()
{
	game = NULL;
	ObjectHandler* h = handler;
	handler = NULL;
	delete h;
	userUI.clear();

}
void GameScene::start()
{
	handler->start();
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
	std::list<GameObject*> objects = handler->getObjects(updatePos,ObjectToGet::getNoBlocks);
	for (GameObject* obj : objects)
		obj->update();
	handler->update();

	//printf("Iloœæ elementów: %d\n", objects.size());


}

void GameScene::addObject(GameObject* obj)
{
	handler->addObject(obj);
}

void GameScene::deleteObject(GameObject* obj)
{
	handler->deleteObject(obj);
}

void GameScene::removeObject(GameObject* obj)
{
	handler->removeObject(obj);
}

void GameScene::draw()
{

	std::list<GameObject*> objects = handler->getObjectsToDraw(cameraPos);


	BeginMode2D(camera);
	for (GameObject* obj : objects)
		obj->draw();
	if(IsKeyDown(KEY_TAB))
		handler->draw();
	EndMode2D();
	DrawText(TextFormat("%.2lf", camera.zoom), 0, 50, 20, BLACK);
	for (UserUI* i : userUI)
		i->drawInterface();
}

void GameScene::removeBlocks(Rectangle pos)
{
	int xIndex = pos.x / tileSize;
	int yIndex = pos.y / tileSize;
	int wMove = pos.width / tileSize;
	int hMove = pos.height / tileSize;
	for (int i = 0; i < wMove; i++)
		for (int j = 0; j < hMove; j++)
			handler->removeBlock(xIndex + i, yIndex + j);
}

void GameScene::deleteBlocks(Rectangle pos)
{
	int xIndex = pos.x / tileSize;
	int yIndex = pos.y / tileSize;
	int wMove = pos.width / tileSize + (int)(pos.width) % tileSize > 0 ? 1 : 0;
	int hMove = pos.height / tileSize + (int)(pos.height) % tileSize > 0 ? 1 : 0;
	handler->deleteBlocks(xIndex, yIndex, wMove, hMove);
}

bool GameScene::addBlock(Block* block)
{
	Rectangle pos = block->getPos();
	int xIndex = pos.x / tileSize;
	int yIndex = pos.y / tileSize;
	int wMove = pos.width / tileSize;
	int hMove = pos.height / tileSize;
	
	std::list<Block*> blocks = handler->getBlocks(xIndex, yIndex, wMove, hMove);
	if (blocks.size() > 0)
		return false;
	for (int x = 0; x < wMove; x++)
		for (int y = 0; y < hMove; y++)
		{
			handler->addBlock(block, x + xIndex, y + yIndex);
		}
	return true;
}

Block* GameScene::getBlock(Rectangle pos)
{
	int xIndex = pos.x / tileSize;
	int yIndex = pos.y / tileSize;
	if (xIndex >= handler->getBlockW() || xIndex < 0)
		return NULL;
	if (yIndex >= handler->getBlockH() || yIndex < 0)
		return NULL;
	return handler->getBlock(xIndex, yIndex);
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
	return handler->getBlocks(xIndex, yIndex, wMove, hMove);
}