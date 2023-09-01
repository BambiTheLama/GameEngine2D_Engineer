#include "Engine.h"
#include "raylib.h"
#include "Controllers/SpriteController.h"
#include "Scenes/GameScene.h"
#include "Scenes/Game/PerlinNoice.h"
#include "../GameObjects/ItemFactory.h"
#include "../GameObjects/BlockFactory.h"
#include "Properties.h"
#include "../GameObjects/RecipesFactory.h"
#include "Scenes/ItemEdytor.h"

Scene* Engine::scene = NULL;

Engine::Engine()
{
	int t = 0;
	std::cin >> t;
	InitWindow(1600, 900, "MyGame");
	InitAudioDevice();
	//SetTargetFPS(60);


	if(t==0)
		scene = new GameScene();
	else
		scene = new ItemEdytor();
	Items;

}
Engine::~Engine()
{

	if (scene)
		delete scene;
	scene = NULL;
	SpriteController::closeSprites();
	Factory::deleteAllFactory();
	Properties* prop = Properties::getProperties();
	if(prop)
		delete prop;
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
	while (!WindowShouldClose())
	{
		time = time2;
		time2 = GetTime();
		deltaTime = time2 - time;

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
	if (IsKeyPressed(KEY_F1) && IsKeyDown(KEY_LEFT_SHIFT))
		Properties::getProperties()->showColliders = !collidersToDraw;
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