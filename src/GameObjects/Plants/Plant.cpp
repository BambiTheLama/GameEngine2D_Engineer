#include "Plant.h"


Plant::Plant(Plant& plant):GameObject(plant)
{

}


Plant::Plant(Rectangle pos,std::string name):GameObject(pos,name)
{

}

Plant::~Plant()
{

}

void Plant::update()
{

}

void Plant::draw()
{

}