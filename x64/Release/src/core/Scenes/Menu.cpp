#include "Menu.h"
#include "../Engine.h"
#include "RecipesEdytor.h"
#include "ItemEdytor.h"
#include "GameScene.h"
#include "TestScene.h"

Menu::Menu()
{
	const int screanW = GetScreenWidth(), screanH = GetScreenHeight();
	const float w = 300,h=64;
	const float x = (screanW - w) / 2;
	const float y = (screanH - h * 3 - (100 - h) * 2) / 3;
	buttons.push_back(new Button({ x,y ,w,h }, "NEW GAME"));
	buttons.push_back(new Button({ x,y + 100,w,h }, "ITEMS CREATOR"));
	buttons.push_back(new Button({ x,y + 200,w,h }, "RECEPIES CREATOR"));
	buttons.push_back(new Button({ x,y + 300,w,h }, "Exit"));
	SetExitKey(KEY_ESCAPE);
	menuTexture = LoadTexture("Resource/Menu.png");
}

Menu::~Menu()
{
	for (auto b : buttons)
	{
		delete b;
	}
	buttons.clear();
	UnloadTexture(menuTexture);
}

void Menu::start()
{

}

void Menu::update(float deltaTime)
{
	for (auto b : buttons)
		b->update(deltaTime);

	if (buttons[0]->press())
	{
		Scene* s = new GameScene();
		s->start();
		Engine::setScene(s);
		return;
	}
	else if (buttons[1]->press())
	{
		Engine::setScene(new ItemEdytor());
		return;
	}
	else if (buttons[2]->press())
	{
		Engine::setScene(new RecipesEdytor());
		return;
	}
	else if (buttons[3]->press())
	{
		Engine::close();
		return;
	}
	
}

void Menu::draw()
{
	
	Rectangle menuPos = { 0,0,menuTexture.width,menuTexture.height };
	Rectangle drawPos = { 0,0,GetScreenWidth(),GetScreenHeight() };
	DrawTexturePro(menuTexture, menuPos, drawPos, { 0,0 }, 0, WHITE);
	for (auto b : buttons)
		b->draw();

}