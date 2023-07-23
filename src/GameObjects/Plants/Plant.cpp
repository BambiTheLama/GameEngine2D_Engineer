#include "Plant.h"


Plant::Plant(Plant& plant):GameObject(plant),ItemsDrop(plant)
{
	sprite = new SpriteController(*plant.sprite);
}


Plant::Plant(Rectangle pos,std::string name):GameObject(pos,name)
{
	std::string path = "Resource/Plants/" + name + ".png";
	sprite = new SpriteController(path.c_str());
}

Plant::~Plant()
{
	delete sprite;
}

void Plant::update()
{

}

void Plant::draw()
{
	sprite->draw(getPos());
}