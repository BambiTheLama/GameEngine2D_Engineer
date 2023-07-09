#include "Engine.h"
#include "raylib.h"
#include "Controllers/SpriteController.h"
#include "Scenes/GameScene.h"
#include "Scenes/Game/PerlinNoice.h"
#include "../GameObjects/ItemFactory.h"
#include "../GameObjects/BlockFactory.h"
Scene* Engine::scene = NULL;

Engine::Engine()
{
	InitWindow(1600, 900, "MyGame");
	InitAudioDevice();
	SetTargetFPS(60);

	scene = new GameScene();
	Items;

}
Engine::~Engine()
{

	if (scene != NULL)
		delete scene;
	scene = NULL;
	SpriteController::closeSprites();
	Items->clearFactory();
	Blocks->clearFactory();
	CloseWindow();
}
void Engine::start()
{
	
	scene->start();
	while (!WindowShouldClose())
	{
		update();
		BeginDrawing();
		ClearBackground(WHITE);
		draw();
		DrawFPS(0, 0);
		EndDrawing();
	}

}

void Engine::update()
{
	scene->update();
}
void Engine::draw()
{
	scene->draw();
}

void Engine::setScene(Scene* scene) 
{
	if (Engine::scene != NULL)
		delete Engine::scene;
	Engine::scene = scene;
}