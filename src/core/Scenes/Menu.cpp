#include "Menu.h"
#include "../Engine.h"
#include "RecipesEdytor.h"
#include "ItemEdytor.h"
#include "GameScene.h"

Menu::Menu()
{
	const int w = 300,h=64;
	buttons.push_back(new Button({ 500,200,w,h }, "NEW GAME"));
	buttons.push_back(new Button({ 500,300,w,h }, "LOAD GAME"));
	buttons.push_back(new Button({ 500,400,w,h }, "ITEMS CREATOR"));
	buttons.push_back(new Button({ 500,500,w,h }, "RECEPIES CREATOR"));
	SetExitKey(KEY_ESCAPE);

}

Menu::~Menu()
{
	for (auto b : buttons)
	{
		delete b;
	}
	buttons.clear();
}

void Menu::start()
{

}

void Menu::update(float deltaTime)
{
	if (!IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		return;
	if (buttons[0]->press())
	{
		Scene* s = new GameScene();
		s->start();
		Engine::setScene(s);
		return;
	}
	else if (buttons[1]->press())
	{

	}
	else if (buttons[2]->press())
	{
		Engine::setScene(new ItemEdytor());
		return;
	}
	else if (buttons[3]->press())
	{
		Engine::setScene(new RecipesEdytor());
		return;
	}
		
	
}

void Menu::draw()
{
	for (auto b : buttons)
		b->draw();
	
}