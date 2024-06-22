#include "Engine.h"
#include "raylib.h"
#include "Controllers/SpriteController.h"
#include "Scenes/GameScene.h"
#include "../GameObjects/ItemFactory.h"
#include "../GameObjects/BlockFactory.h"
#include "Properties.h"
#include "../GameObjects/RecipesFactory.h"
#include "Scenes/ItemEdytor.h"
#include "Scenes/RecipesEdytor.h"
#include "Scenes/Menu.h"

bool Engine::end = false;
Scene* Engine::scene = NULL;

Engine::Engine()
{
	srand(time(NULL));
	InitWindow(1600, 900, "MyGame");
	InitAudioDevice();
	//SetTargetFPS(60);
	scene = new Menu();
}
Engine::~Engine()
{

	if (scene)
		delete scene;
	scene = NULL;


	Properties* prop = Properties::getProperties();
	if(prop)
		delete prop;
	SpriteController::closeSprites();
	Factory::deleteAllFactory();
	RecipesFactory* recipes = CraftingRecipes;
	delete recipes;
	CloseWindow();
}
void Engine::start()
{

	float deltaTime = 0;
	scene->start();
	double time = 0;
	double time2 = GetTime();
	while (!WindowShouldClose() && !end)
	{
		time = time2;
		time2 = GetTime();
		deltaTime = time2 - time;
		if (deltaTime > 0.05)
			deltaTime = 0.05;
		if (IsKeyDown(KEY_LEFT_CONTROL))
			deltaTime *= 0.01;

		update(deltaTime);
		BeginDrawing();
		ClearBackground(DARKBLUE);
		draw();
		//DrawFPS(0, 0);
		EndDrawing();

		
	}

}

void Engine::update(float deltaTime)
{
	scene->update(deltaTime);
	if (IsKeyDown(KEY_LEFT_SHIFT))
	{
		if(IsKeyPressed(KEY_F1))
			Properties::getProperties()->showColliders = !collidersToDraw;
		if (IsKeyPressed(KEY_F2))
			Properties::getProperties()->showPathFinding = !PathFindingShow;
	}

}
void Engine::draw()
{
	scene->draw();
}

void Engine::setScene(Scene* scene) 
{
	if (Engine::scene)
		delete Engine::scene;
	Engine::scene = scene;
}
void Engine::close()
{
	end = true;
}